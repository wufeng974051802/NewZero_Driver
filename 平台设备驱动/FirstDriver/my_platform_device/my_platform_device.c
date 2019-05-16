#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/platform_device.h>
#include <linux/platform_data/clk-lpss.h>

#define NEW_ZERO_DEV_PLATFORM 6666


static struct platform_device my_platform_device = {
	.name			= "newzero",
	.id			= NEW_ZERO_DEV_PLATFORM,
};

static int __init my_platform_device_init(void)
{
       /* 注册平台设备 */
	printk(KERN_WARNING "my_platform_device_init\n");
 	platform_device_register(&my_platform_device);
 	return 0;
}

static void __init my_platform_device_exit(void)
{

   printk(KERN_WARNING "my_platform_device_exit\n");
    /* 注销平台设备 */
     platform_device_unregister(&my_platform_device);
}

module_init(my_platform_device_init);
module_exit(my_platform_device_exit);
MODULE_AUTHOR("newzero");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("my_platform_device");
