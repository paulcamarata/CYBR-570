#!/bin/bash

#add the repo if it does not already exist
if [ ! -f /etc/yum.repos.d/virtualbox.repo ]; then
	sudo wget http://download.virtualbox.org/virtualbox/rpm/rhel/virtualbox.repo -O /etc/yum.repos.d/virtualbox.repo
fi 

#install the latest virtualbox (could dynamically query for this via yum list)
sudo yum install VirtualBox-5.2 -y

#get the ova if it does not already exist
if [ ! -f ~/OSC-2016.ova ]; then
	wget http://people.westminstercollege.edu/faculty/ggagne/osc/vm/OSC-2016.ova -O ~/OSC-2016.ova
fi

#import the OVA to virtualbox
VBoxManage import ~/OSC-2016.ova --vsys 0 --memory 1024 --cpus 2 --eula accept

#force the nic to be bridged (to get a DHCP address on your local network)
#	this works but it is the wrong NIC, may need to find it via 'ip a s' per system
VBoxManage modifyvm OSC-2016 --nic1 bridged --nictype1 virtio --bridgedadapter vmtestbr1

#turn on the VM
VBoxManage startvm "OSC-2016" --type headless

#https://linuxbabe.com/desktop-linux/how-to-install-virtualbox-guest-additions-on-debian-step-by-step
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install build-essential module-assistant
sudo m-a prepare

#add the iso to the system (it automounts on this distro)
sudo sh /media/cdrom/VBoxLinuxAdditions.run


VBoxManage guestproperty get OSC-2016 "/VirtualBox/GuestInfo/Net/0/V4/IP"

#grab the dynamic address from virtualbox and use it to build an SSH session
ssh oscreader@$(VBoxManage guestproperty get OSC-2016 "/VirtualBox/GuestInfo/Net/0/V4/IP" | awk '{print $2}')
