# 编译后生成的目标模块名为 hello_gpio.ko
obj-m := hello_gpio.o
# 交叉编译时，KDIR 指向远程拷贝自开发板的香橙派 5Pro 内核头文件目录
# !!! 注意：请将这里的版本号替换为你自己的内核版本号 !!!
KDIR := $(HOME)/linux-headers-6.1.75-vendor-rk35xx
# 开发板上编译时，KDIR 指向本地内核头文件
# KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
