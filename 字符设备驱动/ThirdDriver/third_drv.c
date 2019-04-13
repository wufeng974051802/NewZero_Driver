#include <linux/module.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DEVICE_NAME "misc_device_second"
static struct miscdevice poll_dev;


ssize_t sys_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	printk("%s\n",__FUNCTION__);
	return 0;
}

ssize_t sys_write(struct device *dev, struct device_attribute *attr,const char *buf, size_t count)
{
	printk("%s\n",__FUNCTION__);
	return count;
}

static struct device_attribute attributes[] ={
	__ATTR(sys_iface_three,S_IRUSR | S_IWUSR, sys_read,sys_write),
};

static int add_sysfs_interfaces(struct device *dev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		if (device_create_file(dev, attributes + i))
			goto undo;

	return 0;
undo:
	for (i--; i >= 0 ; i--)
		device_remove_file(dev, attributes + i);
	dev_err(dev, "%s: failed to create sysfs interface\n", __func__);
	return -ENODEV;
};

static int second_open(struct inode *inode, struct file *file)
{

	return 0;
}

static int second_release(struct inode *node, struct file *filp)
{
	return 0;
}

static struct file_operations second_fops ={
	.owner = THIS_MODULE,
	.open  = second_open,
	.release =dev_release,
	
};

static struct miscdevice second_dev = {
	.minor  = MIS_DYNAMIC_MINOR,
	.name   = DEVICE_NAME,
	.fops   = &second_fops,

};

static init __int second_drv_init(void)
{
	int ret;
	printk("%s\n",__func__);
	ret = misc_register(&second_dev);
	add_sysfs_interfaces(second_dev.this_device);

	return ret;
}

static void __exit second_drv_init(void)
{
	mis_deregister(&second_dev);
	printk("%s\n",__func__);

}
module_init(second_drv_init);
module_exit(second_drv_init);
MODULE_LICENSE("GPL");
