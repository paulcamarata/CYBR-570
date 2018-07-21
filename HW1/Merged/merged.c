#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>

#define BUFFER_SIZE 128

#define PROC1_NAME "jiffies"
#define PROC2_NAME "seconds"
#define MESSAGE "Hello World\n"

/**
 * Function prototypes
 */
ssize_t read_jiffies(struct file *file, char *buf, size_t count, loff_t *pos);
ssize_t read_seconds(struct file *file, char *buf, size_t count, loff_t *pos);


static struct file_operations proc_ops_jiffies = {
        .owner = THIS_MODULE,
        .read = read_jiffies,
};

static struct file_operations proc_ops_seconds = {
        .owner = THIS_MODULE,
        .read = read_seconds,
};

/* This function is called when the module is loaded. */
int proc_init(void)
{

        // creates the /proc/golden entry
        // the following function call is a wrapper for
        // proc_create_data() passing NULL as the last argument
        proc_create(PROC1_NAME, 0, NULL, &proc_ops_jiffies);
        proc_create(PROC2_NAME, 0, NULL, &proc_ops_seconds);

        printk(KERN_INFO "/proc/%s created\n", PROC1_NAME);
        printk(KERN_INFO "/proc/%s created\n", PROC2_NAME);
        printk(KERN_INFO "Jiffies = %lu\n", jiffies);
        printk(KERN_INFO "Golden_Ratio = %lu\n", GOLDEN_RATIO_PRIME);
	return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void) {
        // removes the /proc/golden entry
        remove_proc_entry(PROC1_NAME, NULL);
        remove_proc_entry(PROC2_NAME, NULL);

        printk( KERN_INFO "GCD Result = %lu\n", gcd(3300,24));

        printk( KERN_INFO "/proc/%s removed\n", PROC1_NAME);
        printk( KERN_INFO "/proc/%s removed\n", PROC2_NAME);

}

/**
 * This function is called each time the /proc/golden is read.
 * 
 * This function is called repeatedly until it returns 0, so
 * there must be logic that ensures it ultimately returns 0
 * once it has collected the data that is to go into the 
 * corresponding /proc file.
 *
 * params:
 *
 * file:
 * buf: buffer in user space
 * count:
 * pos:
 */
ssize_t read_jiffies(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "Jiffies = %lu\n", jiffies);

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}

ssize_t read_seconds(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "Seconds = %lu\n", jiffies/HZ);

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}

/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Golden Module");
MODULE_AUTHOR("Paul Camarata");
