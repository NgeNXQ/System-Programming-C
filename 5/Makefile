obj-m += mytimemodule.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc main.c -o labwork5

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm labwork5