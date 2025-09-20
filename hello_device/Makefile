# 当前目录（驱动源码所在目录）
PWD := $(shell pwd)
# 目标模块名
obj-m := hello_device.o
# 交叉编译时，KDIR 指向远程拷贝自开发板的内核头文件目录
# !!! 注意：请根据你自己的开发板内核头文件目录进行修改 !!!
KDIR := $(HOME)/linux-headers-6.1.75-vendor-rk35xx
# 开发板上编译时，KDIR 指向系统已安装内核头文件
# KDIR := /lib/modules/$(shell uname -r)/build

# 编译规则
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
