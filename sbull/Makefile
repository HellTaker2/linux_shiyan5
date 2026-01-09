# 注释/取消注释以下行以禁用/启用调试
#DEBUG = y


# 将调试标志（或不添加）添加到 CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DSBULL_DEBUG # "-O" 需要用来展开内联函数
else
  DEBFLAGS = -O2
endif

EXTRA_CFLAGS += $(DEBFLAGS)
# 用于处理 switch case 中 RM_SIMPLE 的 fall through 警告
EXTRA_CFLAGS += -I.. -Wno-implicit-fallthrough

ifneq ($(KERNELRELEASE),)
# 从内核构建系统调用

obj-m	:= sbull.o

else
# 当 KERNELRELEASE 未定义时，表示是用户直接调用make
# 这个分支用于设置环境并调用内核构建系统

# KERNELDIR: 内核构建目录，默认为当前运行内核的构建目录
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
# PWD: 模块源代码所在的目录
PWD       := $(shell pwd)

# 调用内核构建系统编译模块
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	# -C $(KERNELDIR): 切换到内核目录 M=$(PWD): 指定模块源代码目录 modules: 编译模块的目标

endif


# clean 目标 - 清理编译生成的文件
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers

# 依赖关系生成目标
# 三个目标指向同一个命令，提供不同的调用方式
depend .depend dep:
	$(CC) $(EXTRA_CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include .depend
endif
