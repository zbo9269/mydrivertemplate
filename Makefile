ifneq ($(KERNELRELEASE),)
    obj-m += driver.o
else
    PWD :=$(shell pwd)
    KVER := $(shell uname -r)
    KDIR :=/lib/modules/$(KVER)/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mv ./driver.ko ./modules/driver.ko
clean:
	rm -rf *.o *.mod.c *.ko */*.ko *.symvers *order *.markers .driver* .tmp* 
endif
