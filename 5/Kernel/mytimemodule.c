#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>

#include <linux/time.h>
#include <linux/sched.h>

MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Babich Denys");
MODULE_DESCRIPTION("Kernel module to provide the current time");

#define BUFFER_LENGTH 256
#define MSG_PREF "Labwork5: "
#define print_message(msg, ...) printk(KERN_ERR MSG_PREF msg, ##__VA_ARGS__);

dev_t devt = 0;
static struct cdev my_cdev;
static struct device* dev = NULL;
static struct class* dev_class = NULL;

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
	const int SECONDS_IN_HOUR = 3600;
    	const int SECONDS_IN_MINUTE = 60;
    	

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

	if ((res = alloc_chrdev_region(&devt, 0, 1, "my_cdev")) < 0) 
	{
		print_message("Cannot allocate major number\n");
		return res;
	}

	print_message("Major = %d Minor = %d\n", MAJOR(devt), MINOR(devt));

	cdev_init(&my_cdev, &fops);

	if ((res = cdev_add(&my_cdev, devt, 1)) < 0) 
	{
		print_message("Cannot add the device to the system\n");
		unregister_chrdev_region(devt, 1);
		return res;
	}

	dev_class = class_create(THIS_MODULE, "my_class");

	if (IS_ERR(dev_class)) 
	{
		res = PTR_ERR(dev_class);
		print_message("Cannot create the struct class\n");
		unregister_chrdev_region(devt, 1);
		return res;
	}

	// create branch of driver /dev/my_cdev
	dev = device_create(dev_class, NULL, devt, NULL, "my_cdev");

	if (IS_ERR(dev))
	{
		res = PTR_ERR(dev);
		class_destroy(dev_class);
		unregister_chrdev_region(devt, 1);
		print_message("Cannot create the Device\n");
		return res;
	}

	print_message("Device Driver Insert...Done!!!\n");
	return 0;
}

static void __exit mytimemodule_exit(void) 
{
	cdev_del(&my_cdev);
	class_destroy(dev_class);
	device_destroy(dev_class, devt);
	unregister_chrdev_region(devt, 1);
	print_message("Device Driver Remove...Done!!!\n");
}

module_init(mytimemodule_init);
module_exit(mytimemodule_exit);
