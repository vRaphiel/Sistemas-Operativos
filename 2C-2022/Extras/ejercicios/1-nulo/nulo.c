#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

static dev_t nulo_num;
static struct cdev cdev_nulo;
static struct class *nulo_clase;

static ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
	printk(KERN_ALERT "Lectura de modulo");
	return 0;
}

static ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
	printk(KERN_ALERT "Escritura de modulo");
	return s;
}

static struct file_operations nulo_operaciones = {
	.owner = THIS_MODULE,
	.read = nulo_read,
	.write = nulo_write
};

static int __init nulo_init(void) {
	printk(KERN_ALERT "Carga de modulo nulo\n");

	cdev_init(&cdev_nulo, &nulo_operaciones);

	alloc_chrdev_region(&nulo_num, 0, 1, "nulo");

	cdev_add(&cdev_nulo, nulo_num, 1);

	nulo_clase = class_create(THIS_MODULE, "nulo");
	
	device_create(nulo_clase, NULL, nulo_num, NULL, "nulo");

	printk(KERN_ALERT "%d numero", nulo_num);
	
	return 0;
}

static void __exit nulo_exit(void) {
	printk(KERN_ALERT "Descarga de modulo nulo\n");

	unregister_chrdev_region(nulo_num, 1);
	cdev_del(&cdev_nulo);

	device_destroy(nulo_clase, nulo_num);
	class_destroy(nulo_clase);
	
}

module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de '/dev/null'");