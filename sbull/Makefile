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

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif



clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers

depend .depend dep:
	$(CC) $(EXTRA_CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include .depend
endif
