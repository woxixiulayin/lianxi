obj-m += hello.o
#KERNEL_VERSION = /lib/modules/$(shell uname -r)/build/
KERNEL_VERSION = /usr/src/linux-source-2.6.32/
all:
	make -C $(KERNEL_VERSION) M=$(PWD) modules
clean:
	make -C $(KERNEL_VERSION) M=$(PWD) clean

