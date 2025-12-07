#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/random.h>

int upper_bound;

static ssize_t azar_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
	
	
	char* buffer;
	int number;

	buffer = (char *)kmalloc(s+1, GFP_KERNEL);

	//get_random_bytes(&number, sizeof(number));

	snprintf(buffer, s+1, "%d\n", 5);

	
	copy_to_user(data, &number, s);
	kfree(buffer);

	return 0;
}

static ssize_t azar_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {

	char* buffer;

	buffer = (char *) kmalloc(s+1, GFP_KERNEL);

	if(buffer == NULL) {
		return -ENOMEM;
	}

	copy_from_user(buffer, data, s);
	if(kstrtoint(buffer+'\0', 10, &upper_bound) != 0) {
		return -EPERM;
	}

	kfree(buffer);

	return 0;
}

static struct file_operations azar_operaciones = {
	.owner = THIS_MODULE,
	.read = azar_read,
	.write = azar_write,
};

static struct cdev azar_device;
static dev_t major;
static struct class *azar_class;

static int __init hello_init(void) {
	cdev_init(&azar_device, &azar_operaciones);
	alloc_chrdev_region(&major, 0, 1, "azar");
	cdev_add(&azar_device, major, 1);

	azar_class = class_create(THIS_MODULE, "azar");
	device_create(azar_class, NULL, major, NULL, "azar");

	printk(KERN_ALERT "Cargando modulo 'azar'\n");
	return 0;
}

static void __exit hello_exit(void) {
	device_destroy(azar_class, major);
	class_destroy(azar_class);

	unregister_chrdev_region(major, 1);
	cdev_del(&azar_device);

	printk(KERN_ALERT "Descargando modulo 'azar'.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de '/dev/azar'");
