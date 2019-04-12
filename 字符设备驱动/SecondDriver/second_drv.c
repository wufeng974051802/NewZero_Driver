
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
#include <linux/platform_device.h>


static  char mybuf[100]="123";
static ssize_t show_my_device(struct device *dev, struct device_attribute *attr,char *buf)  //cat命令时,将会调用该函数
{
	//printk("%s\n",__FUNCTION__);
	return sprintf(buf, "%s\n", mybuf);
}

static ssize_t set_my_device(struct device *dev, struct device_attribute *attr,const char *buf, size_t count) //echo命令时,将会调用该函数
{
	
	//sprintf(mybuf, "%s", buf);
	memset(mybuf,0,sizeof(mybuf));
	strncpy(mybuf,buf,count);
	printk("%s  mybuf%s count=%d \n",__FUNCTION__,mybuf,count);
	//如果字符串相等打开手电筒
        if(strncmp(mybuf, "1234",count-1) == 0)
	   gpio_direction_output(7,1);
	else
	    gpio_direction_output(7,0);
	return count;
}
static DEVICE_ATTR(my_device_test, S_IWUSR|S_IRUSR, show_my_device, set_my_device);
                //定义一个名字为my_device_test的设备属性文件


static int second_drv_open (struct inode *inode, struct file *file){

	printk("first_drv_open\n");
	return 0;
}

static int second_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos){
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


static struct file_operations second_drv_fops = {
	.owner = THIS_MODULE,
	.open  = second_drv_open,
	.write = second_drv_write,
	
};

int major;
static struct class *cls;
static struct device *dev;
static int second_drv_init(void)
{
	major = register_chrdev(0,"second_drv",&second_drv_fops);
	cls = class_create(THIS_MODULE,"xyz_class");
	dev = device_create(cls,0,MKDEV(major,0),NULL,"xyz_device");  //创建xyz_device设备 
	
	//创建sys属性节点
	//device_create_file(struct device *dev, const struct device_attribute *attr)
	//sysfs_create_file(struct kobject * kobj, const struct attribute * attr);
	//sysfs_create_file(&(dev->kobj), &dev_attr_my_device_test.attr);
        device_create_file(dev, &dev_attr_my_device_test);
       
	////申请LED gpio
        gpio_request(7,"vvvvvvv");
      
	return 0;
}

void second_drv_exit(void)
{
	 device_destroy(cls, MKDEV(major,0));
         class_destroy(cls);
         unregister_chrdev(major, "second_drv");
	
}



module_init(second_drv_init);
module_exit(second_drv_exit);
MODULE_LICENSE("GPL");

/*

static ssize_t show_my_device(struct device *dev,
                  struct device_attribute *attr, char *buf)   //cat命令时,将会调用该函数
{
    return buf;
}

static ssize_t set_my_device(struct device *dev,
                 struct device_attribute *attr,
                 const char *buf, size_t len)   //echo命令时,将会调用该函数.
{
    return len;
}
static DEVICE_ATTR(my_device_test, S_IWUSR|S_IRUSR, show_my_device, set_my_device);   //定义一个名字为my_device_test的设备属性文件

其中
DEVICE_ATTR()定义位于include/linux/device.h中,定义如下所示:
#define DEVICE_ATTR(_name, _mode, _show, _store) \
    struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)


#define __ATTR(_name,_mode,_show,_store) {                              \
        .attr = {.name = __stringify(_name), .mode = _mode },           \
        .show   = _show,                                                \
        .store  = _store,                                               \
}



所以static DEVICE_ATTR(my_device_test, S_IWUSR|S_IRUSR, show_my_device, set_my_device); 将其展开为:

struct device_attribute dev_attr_my_device_test ={  
    .attr = {.name = "my_device_test", .mode = S_IWUSR|S_IRUSR },     
    .show    = show_my_device,                 
    .store    = set_my_device,             
}
类似的还有
如对设备的使用        DEVICE_ATTR   
对驱动使用               DRIVER_ATTR
对总线使用               BUS_ATTR 
对类别 (class) 使用  CLASS_ATTR


device_create_file创建sysfs节点
类似的还有 
　device_create_file　　　为设备创建sys的节点。 
　bus_create_file 　　　　为总线创建sys的节点。 
　driver_create_file　　　为驱动创建sys的节点。
*/

