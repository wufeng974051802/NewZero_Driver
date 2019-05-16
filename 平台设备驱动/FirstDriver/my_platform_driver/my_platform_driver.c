
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

static int my_platform_driver_probe(struct platform_device *pdev)
{
	printk(KERN_WARNING "my_platform_driver_probe\n");
	return 0;
};

static struct platform_driver my_platform_driver = 
{
	.probe = my_platform_driver_probe,
	.driver = {
		.name = "newzero"

	}
};


static int __init my_platform_driver_init(void)
{	
         printk(KERN_WARNING "my_platform_driver_init\n");
	 /* 注册平台驱动 */
	return platform_driver_register(&my_platform_driver);
}

static void __init my_platform_driver_exit(void)
{
	printk(KERN_WARNING "my_platform_driver_exit\n");
　　　　　　　　/* 卸载平台驱动 */
	platform_driver_unregister(&my_platform_driver);
}
module_init(my_platform_driver_init);
module_exit(my_platform_driver_exit);
MODULE_AUTHOR("newzero");
MODULE_DESCRIPTION("my_platform_driver");
MODULE_LICENSE("GPL");
