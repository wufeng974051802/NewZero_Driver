# NewZero_Driver

1.FirstDriver ---创建一个字符设备并新建一个节点(/dev/xyz)的Demo =不可以echo
              ---frist_drv.c 字符设备程序　Makefile编译
　　　　　　　　　　　　　 ---first_drv_main.c 测试程序　Android.mk编译


2.SecondDriver --创建一个字符设备并新建一个(sys属性节点)的Demo 
	      ----其中device/xyz_device为设备节点
	      ----sys/devices/virtual/xyz_class/xyz_device/my_device_test为属性节点。可以echo
