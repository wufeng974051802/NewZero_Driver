#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/gpio_keys.h>
#include <asm/gpio.h>
/**
实现键盘驱动,让开发板的4个按键代表键盘中的L、S、空格键、回车键
 struct input_dev *input_allocate_device(void);  //向内核中申请一个input_dev设备,然后返回这个设备
input_unregister_device(struct input_dev *dev);   //卸载/sys/class/input目录下的input_dev这个类设备, 一般在驱动出口函数写
input_free_device(struct input_dev *dev);   //释放input_dev这个结构体, 一般在驱动出口函数写
set_bit(nr,p);                  //设置某个结构体成员p里面的某位等于nr,支持这个功能
/* 比如:
set_bit(EV_KEY,buttons_dev->evbit);   //设置input_dev结构体buttons_dev->evbit支持EV_KEY
set_bit(KEY_S,buttons_dev->keybit);  //设置input_dev结构体buttons_dev->keybit支持按键”S”
*/

// void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value);  //上报事件
 // input_dev *dev :要上报哪个input_dev驱动设备的事件
 // type : 要上报哪类事件, 比如按键事件,则填入: EV_KEY
 // code: 对应的事件里支持的哪个变量，比如按下按键L则填入: KEY_L
 //value:对应的变量里的数值,比如松开按键则填入1,松开按键则填入0
	

**/
struct input_dev *buttons_dev;//定义一个input_devi结构体
static struct timer_list buttons_timer;    //定时器结构体  


static int first_drv_init(void){
	//1.向内核 申请input_dev结构体
	buttons_dev = input_allocate_device();
	//2.设置支持的按键类型
	set_bit(EV_KEY,buttons_dev->evbit);//支持键盘事件
        set_bit(EV_REP,buttons_dev->evbit);       //支持键盘重复按事件
	
	//3.注册input_dev
	input_register_device(buttons_dev);

	return 0;
}

void first_drv_exit(void){


}

module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_LICENSE("GPL");
