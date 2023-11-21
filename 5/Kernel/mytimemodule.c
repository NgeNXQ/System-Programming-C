#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/time.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>

MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Babich Denys");
MODULE_DESCRIPTION("Kernel module to provide the current time");

#define BUFFER_LENGTH 256
#define MSG_PREF "Labwork5: "
#define print_message(msg, ...) printk(KERN_ERR MSG_PREF msg, ##__VA_ARGS__);

dev_t device_number = 0;
static struct cdev character_device;
static struct device* device = NULL;
static struct class* device_class = NULL;

static int open(struct inode*, struct file*);
static int release(struct inode*, struct file*);
static ssize_t read(struct file*, char __user*, size_t, loff_t*);

static struct file_operations fops = { 
	.read = read,
	.open = open,
	.release = release
};

static int open(struct inode* inode, struct file* file)
{
	print_message("File has been opened\n");
	return 0;
}

static ssize_t read(struct file* file, char __user* buffer, size_t count, loff_t* offset)
{
	const int TIMEZONE_OFFSET = 2;
    char data[BUFFER_LENGTH] = { 0 };

    struct tm tm_info_utc;
    time64_to_tm(ktime_get_real_seconds(), 0, &tm_info_utc);

    tm_info_utc.tm_hour += TIMEZONE_OFFSET;
    	
    if (tm_info_utc.tm_hour >= 24) 
        tm_info_utc.tm_hour -= 24;

    snprintf(data, BUFFER_LENGTH, "%02d:%02d:%02d", tm_info_utc.tm_hour, tm_info_utc.tm_min, tm_info_utc.tm_sec);

	if (count > BUFFER_LENGTH)
		count = BUFFER_LENGTH;

	if (copy_to_user(buffer, data, count))
		return -EFAULT;

	return count;
}

static int release(struct inode* inode, struct file* file)
{
	print_message("File has been released\n");
	return 0;
}

static int __init mytimemodule_init(void) 
{
	long res = 0;

	if ((res = alloc_chrdev_region(&device_number, 0, 1, "character_device")) < 0)
	{
		print_message("Cannot allocate major number\n");
		return res;
	}

	print_message("Major = %d Minor = %d\n", MAJOR(device_number), MINOR(device_number));

	cdev_init(&character_device, &fops);

	if ((res = cdev_add(&character_device, device_number, 1)) < 0)
	{
		print_message("Cannot add the device to the system\n");
		unregister_chrdev_region(device_number, 1);
		return res;
	}

	device_class = class_create(THIS_MODULE, "device_class");

	if (IS_ERR(dev_class)) 
	{
		res = PTR_ERR(device_class);
		print_message("Cannot create the struct class\n");
		unregister_chrdev_region(device_number, 1);
		return res;
	}

	device = device_create(device_class, NULL, device_number, NULL, "character_device");

	if (IS_ERR(labwork5_device))
	{
		res = PTR_ERR(device);
		class_destroy(device_class);
		unregister_chrdev_region(device_number, 1);
		print_message("Cannot create the Device\n");
		return res;
	}

	print_message("mytimemodule has been initialized.\n");
	return 0;
}

static void __exit mytimemodule_exit(void) 
{
	cdev_del(&character_device);
	class_destroy(device_class);
	unregister_chrdev_region(device_number, 1);
	device_destroy(device_class, device_number);
	print_message("mytimemodule has been deallocated.\n");
}

module_init(mytimemodule_init);
module_exit(mytimemodule_exit);