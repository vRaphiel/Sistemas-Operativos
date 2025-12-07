#include <linux/init.h>
#include <linux/module.h> // THIS_MODULE
#include <linux/kernel.h> // Kernel cosas
#include <linux/fs.h>     // File operations
#include <linux/cdev.h>   // Char devices
#include <linux/device.h> // Nodos filesystem
#include <linux/uaccess.h> // copy_to_user
#include <linux/slab.h>    // kmalloc
#include <linux/random.h>  // get_random_bytes

static dev_t azar_num;
static struct cdev cdev_azar;
static struct class *azar_clase;
static char* numero_convertir = NULL;

static ssize_t azar_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
	return 0;
}

static ssize_t azar_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
	kmalloc(sizeof(data) + 3, GFP_KERNEL);

	copy_from_user(numero_convertir, data, 1);
	copy_from_user(numero_convertir, "\0", 1);

	printk(KERN_ALERT "%s", numero_convertir);
	// kmalloc(s, GFP_KERNEL);
	return s;
}

static struct file_operations azar_operaciones = {
	.owner = THIS_MODULE,
	.read = azar_read,
	.write = azar_write
};

static int __init azar_init(void) {
	printk(KERN_ALERT "Carga de modulo azar\n");

	cdev_init(&cdev_azar, &azar_operaciones);

	alloc_chrdev_region(&azar_num, 0, 1, "azar");

	cdev_add(&cdev_azar, azar_num, 1);

	azar_clase = class_create(THIS_MODULE, "azar");
	
	device_create(azar_clase, NULL, azar_num, NULL, "azar");

	printk(KERN_ALERT "%d numero", azar_num);
	
	return 0;
}

static void __exit azar_exit(void) {
	printk(KERN_ALERT "Descarga de modulo azar\n");

	unregister_chrdev_region(azar_num, 1);
	cdev_del(&cdev_azar);

	device_destroy(azar_clase, azar_num);
	class_destroy(azar_clase);
	
}

module_init(azar_init);
module_exit(azar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Generador de números al azar");