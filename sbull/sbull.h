
/*
 * sbull.h -- 字符模块的定义
 *
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * 本文件中的源代码可以自由使用、修改和以源代码或二进制形式重新分发，
 * 只要在派生的源文件中保留致谢声明即可。
 * 引用应列出代码来自 Alessandro Rubini 和 Jonathan Corbet 编写的
 * 《Linux Device Drivers》一书，由 O'Reilly & Associates 出版。
 * 不附带任何担保；我们不对错误或适用性承担责任。
 *
 */


#include <linux/ioctl.h>

i
/* 多队列仅在 2.4 内核上工作 */
#ifdef SBULL_MULTIQUEUE
#    warning "Multiqueue only works on 2.4 kernels"
#endif

/*
 * 帮助调试的宏
 */

#undef PDEBUG             /* 取消定义，以防万一 */
#ifdef SBULL_DEBUG
#  ifdef __KERNEL__
     /* 如果开启了调试且在内核空间，则使用 printk 打印调试信息 */
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "sbull: " fmt, ## args)
#  else
     /* 如果在用户空间，则打印到标准错误输出 */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* 未开启调试：什么也不做 */
#endif

#undef PDEBUGG
#define PDEBUGG(fmt, args...) /* 占位符：什么也不做 */


#define SBULL_MAJOR 0       /* 默认动态分配主设备号 */
#define SBULL_DEVS 2        /* 两个磁盘设备 */
#define SBULL_RAHEAD 2      /* 预读两个扇区 */
#define SBULL_SIZE 2048     /* 每个设备 2MB */
#define SBULL_BLKSIZE 1024  /* 块大小 1KB */
#define SBULL_HARDSECT 512  /* 硬件扇区大小 512字节 (2.2 和 2.4 内核可以使用不同的值) */

#define SBULLR_MAJOR 0      /* 原始设备的动态主设备号 */

/*
 * sbull 设备是可移除的：如果关闭超过半分钟，它将被移除。
 * 因此使用引用计数和内核定时器来管理。
 */

typedef struct Sbull_Dev {
   int size;                    /*INT  设备大小 */
   int usage;                   /*INT  使用计数 */
   struct timer_list timer;     /* 定时器，用于模拟介质移除 */
   spinlock_t lock;             /* 自旋锁，用于互斥访问 */
   u8 *data;                    /* 数据缓冲区指针 */
#ifdef SBULL_MULTIQUEUE
   request_queue_t *queue;      /* 请求队列 */
   int busy;                    /* 忙碌标志 */
#endif
}              Sbull_Dev;
