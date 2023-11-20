#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/uaccess.h>

MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Babich Denys");
MODULE_DESCRIPTION("Kernel module to provide the current time");

#define BUF_LEN 256

#define MSG_PREF "Labwork5: "
#define print_msg(msg, ...) printk(KERN_ERR MSG_PREF msg, ##__VA_ARGS__);

// structures for creation of symbolic driver
dev_t devt = 0;
static struct class* dev_class = NULL;
static struct cdev my_cdev;
static struct device* dev = NULL;

static int def_open(struct inode* inode, struct file* file);
static int def_release(struct inode* inode, struct file* file);
static ssize_t def_read(struct file* filp, char __user* buf, size_t len, loff_t* off);
//static ssize_t def_write(struct file* filp, const char* buf, size_t len, loff_t* off);
//static long def_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);

// structure that includes pointers to definitions of operations for the device
static struct file_operations fops = {
	//.owner = THIS_MODULE,
	.read = def_read,
	//.write = def_write,
	.open = def_open,
	.release = def_release,
	//.unlocked_ioctl = def_ioctl,
};

static int def_open(struct inode* inode, struct file* file) {
	print_msg("Open function is called\n");
	return 0;
}

static int def_release(struct inode* inode, struct file* file) {
	print_msg("Release function is called\n");
	return 0;
}

static ssize_t def_read(struct file* filp, char __user* buf, size_t len, loff_t* off) {
	uint8_t data[BUF_LEN] = { 0 };
	struct timespec64 t;
	print_msg("Read function is called\n");
	// function for getting time
	ktime_get_real_ts64(&t);
	snprintf(data, BUF_LEN, "Current time(sec: %llu, mircosec: %lu)", t.tv_sec, t.tv_nsec);

	if (len > BUF_LEN) {
		len = BUF_LEN;
	}

	// function for safe copying of data from the kernel space into user space
	if (copy_to_user(buf, data, len)) {
		return -EFAULT;
	}

	return len;
}

//static ssize_t def_write(struct file* filp, const char __user* buf, size_t len, loff_t* off) {
//	print_msg("Write function is called\n");
//	return len;
//}

//static long def_ioctl(struct file* filp, unsigned int cmd, unsigned long arg) {
//	print_msg("Ioctl function is called\n");
//	return 0;
//}

static int __init mytimemodule_init(void) {
	long res = 0;
	// chardev allocation
	if ((res = alloc_chrdev_region(&devt, 0, 1, "my_cdev")) < 0) {
		print_msg("Cannot allocate major number\n");
		return res;
	}
	print_msg("Major = %d Minor = %d\n", MAJOR(devt), MINOR(devt));

	// initialize new driver
	cdev_init(&my_cdev, &fops);
	// add driver to the system
	if ((res = cdev_add(&my_cdev, devt, 1)) < 0) {
		print_msg("Cannot add the device to the system\n");
		unregister_chrdev_region(devt, 1);
		return res;
	}

	// create class sysfs
	dev_class = class_create(THIS_MODULE, "my_class");
	// exeption handling
	if (IS_ERR(dev_class)) {
		res = PTR_ERR(dev_class);
		print_msg("Cannot create the struct class\n");
		unregister_chrdev_region(devt, 1);
		return res;
	}

	// create branch of driver /dev/my_cdev
	dev = device_create(dev_class, NULL, devt, NULL, "my_cdev");
	// exeption handling
	if (IS_ERR(dev)) {
		res = PTR_ERR(dev);
		print_msg("Cannot create the Device\n");
		class_destroy(dev_class);
		unregister_chrdev_region(devt, 1);
		return res;
	}

	print_msg("Device Driver Insert...Done!!!\n");
	return 0;
}

static void __exit mytimemodule_exit(void) {
	device_destroy(dev_class, devt);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(devt, 1);
	print_msg("Device Driver Remove...Done!!!\n");
}

module_init(mytimemodule_init);
module_exit(mytimemodule_exit);