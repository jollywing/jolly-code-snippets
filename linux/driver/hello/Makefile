
# 使用 := 给变量赋值，obj-m := $(foo), 变量定义的时候$(foo)的值就被展开，即使以后foo的值再变化，obj-m的值也不会再变。

ifneq ($(KERNELRELEASE),)
# 告诉make有一个模块需要从hello.o构建。
	obj-m := hello.o

# 调用shell命令，必须用 $(shell xxx) 的形式，如果直接使用 $(xxx), Make还以为是变量呢。

# ?= 表示如果左边的变量没有赋值过，就赋值为右边的值。
else

	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

# M=$(PWD) 让make在构造modules之前返回源代码目录
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	-rm -f *.mod.c *.order *.symvers *.o *.ko
