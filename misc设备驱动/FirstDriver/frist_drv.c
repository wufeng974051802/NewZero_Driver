
#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h> //struct miscdevice
#include <linux/fs.h> //strcut file_operations
#include <asm/gpio.h>
#include <linux/uaccess.h> //copy_*
#include <linux/cdev.h>
#include <linux/leds.h>  
#include <linux/io.h>  
#include <linux/ioport.h>
#include <linux/gpio.h>
/*
使用misc_register，在加载模块时会自动创建设备文件，为主设备号为10的字符设备。
使用misc_deregister，在卸载模块时会自动删除设备文件

/*  misedevice 结构：
struct miscdevice  {
    int minor; //次设备号，若为 MISC_DYNAMIC_MINOR 自动分配
    const char *name; //设备名
    struct file_operations *fops; //设备操作
    struct list_head list;
    struct device *dev;
    struct class_device *class;
    char devfs_name[64];
};
*/

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

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULE,
	.open  = first_drv_open,
	.write = first_drv_write,
};

static struct miscdevice first_misc = {
	.minor = MISC_DYNAMIC_MINOR, //内核分配次设备号
	.name  = "xyz",//设备文件名，内核自动创建/dev/myled
	.fops = &first_drv_fops//混杂设备对象具有的硬件操作方法
};


static int first_drv_init(void){

	//注册混杂设备对象到内核
	 misc_register(&first_misc);
	//申请LED gpio
        gpio_request(7,"vvvvvvv");

	return 0;
}

void first_drv_exit(void){

	//卸载混杂设备对象
	misc_deregister(&first_misc);

}

module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_LICENSE("GPL");
