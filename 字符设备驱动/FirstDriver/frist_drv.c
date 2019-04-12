
#include <linux/module.h>
#include <linux/reboot.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/pci.h>
#include <linux/time.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <scsi/scsi.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_tcq.h>
#include <scsi/scsi_cmnd.h>
#include <linux/cdev.h>
#include <linux/leds.h>  
#include <linux/io.h>  
#include <linux/ioport.h>
#include <linux/gpio.h>


static struct class *first_drv_class;
static struct device *first_drv_devs;

static int first_drv_open (struct inode *inode, struct file *file){

	printk("first_drv_open\n");
	return 0;
}

static int first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos){
	int val;
	copy_from_user(&val, buf, count);//从用户空间拷贝数据

	printk("first_drv_write  copy_from_user =%d\n",val);

	if(val == 1){
		//打开LED
		//gpio_request(7,"vvvvvvv");
	        gpio_direction_output(7,1);
		
	}else{
		//gpio_request(7,"vvvvvvv");
	        gpio_direction_output(7,0);
	}

	return 0;
}

static struct file_operations first_drv_fopes = {
	.owner = THIS_MODULE,
	.open  = first_drv_open,
	.write = first_drv_write,
};


int major;

static int first_drv_init(void){

	printk("first_drv_init\n");
	//1.注册字符设备
	major = register_chrdev(0,"first_drv", &first_drv_fopes);
       //2.创建类
	first_drv_class = class_create(THIS_MODULE,"first_drv");
	if(IS_ERR(first_drv_class))
		return PTR_ERR(first_drv_class);
	//3.在类中创建一个设备
	first_drv_devs = device_create(first_drv_class, NULL,MKDEV(major, 0),NULL, "xyz");  // /dev/xyz


	if(unlikely(IS_ERR(first_drv_devs)))
			return PTR_ERR(first_drv_devs);

	//申请LED gpio
        gpio_request(7,"vvvvvvv");

	return 0;
}

void first_drv_exit(void){
	unregister_chrdev(major,"first_drv");

	device_unregister(first_drv_devs);

	class_destroy(first_drv_class);


}

module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_LICENSE("GPL");
