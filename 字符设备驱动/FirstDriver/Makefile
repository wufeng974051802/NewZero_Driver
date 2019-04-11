ifeq ($(KERNELRELEASE),)

KERNELDIR_OUT ?=/home/water/workspace/Server/169test/code/ZHANXUN/A351_debug/MOCOR5_SFPHONE_17F_RLS1_W18.19/idh.code/out/target/product/sp9820e_2h10/obj/KERNEL
CROSS_COMPILE ?= /home/water/workspace/Server/169test/code/ZHANXUN/A351_debug/MOCOR5_SFPHONE_17F_RLS1_W18.19/idh.code/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-

PWD :=$(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR_OUT) M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clear:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order  Module.symvers
.PHONY: modules modules_install clean
else
	obj-m:= first_drv_main.o
#	obj-m:= aw87339_audio.o
endif
