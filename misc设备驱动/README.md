# NewZero_Driver
因为这些字符设备不符合预先确定的字符设备范畴，所有这些设备采用主编号10 ，一起归于misc device，其实misc_register就是
用主标号10调用register_chrdev()的,各个混杂设备个体通过次设备号来区分。也就是说，misc设备其实也就是特殊的字符设备，
可自动生成设备节点。；

1.FirstDriver   ------添加一个节点的混杂设备
