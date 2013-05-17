obj-m = gclip.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo rm /dev/gclip || true
	sudo rmmod gclip
	sudo insmod /home/anthony/dev/c/modules/gclip/gclip.ko
	sudo mknod /dev/gclip c 250 0
	sudo chmod 777 /dev/gclip

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

