#include <linux/fs.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "current_time_device"
#define CLASS_NAME "current_time_class"

MODULE_VERSION("1.0");
MODULE_LICENSE("MIT");
MODULE_AUTHOR("Babich Denys");
MODULE_DESCRIPTION("Kernel module to provide the current time");

static int majorNumber;
static struct class* current_time_class = NULL;
static struct device* current_time_device = NULL;

static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);

static int device_open_count = 0;

static struct file_operations fops = 
{
    .open = device_open,
    .read = device_read,
    .release = device_release,
};

static int __init mytimemodule_init(void) 
{
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);

    if (majorNumber < 0) 
    {
        printk(KERN_ALERT "Failed to register a major number\n");
        return majorNumber;
    }

    current_time_class = class_create(THIS_MODULE, CLASS_NAME);

    if (IS_ERR(current_time_class)) 
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(current_time_class);
    }

    current_time_device = device_create(current_time_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);

    if (IS_ERR(current_time_device)) 
    {
        class_destroy(current_time_class);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(current_time_device);
    }

    printk(KERN_INFO "Kernel module is loaded\n");
    return 0;
}

static void __exit mytimemodule_exit(void)
{
    device_destroy(current_time_class, MKDEV(majorNumber, 0));
    class_unregister(current_time_class);
    class_destroy(current_time_class);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "Kernel module is unloaded\n");
}

static int device_open(struct inode* inode, struct file* file) 
{
    if (device_open_count) 
    {
        return -EBUSY;
    }

    device_open_count++;
    try_module_get(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file* file, char* buffer, size_t length, loff_t* offset) 
{
    struct timespec current_time;
    getnstimeofday(&current_time);

    char time_string[100];
    snprintf(time_string, sizeof(time_string), "Current time: %ld.%09ld\n", current_time.tv_sec, current_time.tv_nsec);

    int error_count = copy_to_user(buffer, time_string, strlen(time_string));

    if (error_count == 0) 
    {
        return strlen(time_string);
    }
    else 
    {
        printk(KERN_ALERT "Failed to send data to the user\n");
        return -EFAULT;
    }
}

static int device_release(struct inode* inode, struct file* file) 
{
    device_open_count--;
    module_put(THIS_MODULE);
    return 0;
}

module_init(mytimemodule_init);
module_exit(mytimemodule_exit);
