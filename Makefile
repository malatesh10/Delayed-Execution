obj-m += delay-usleep.o

KDIR = /lib/modules/$(shell uname -r)/build
make:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean

