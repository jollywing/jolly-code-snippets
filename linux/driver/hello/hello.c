#include <linux/init.h>
#include <linux/module.h>

/* 告诉内核该模块使用自由许可证 */
MODULE_LICENSE("Dual BSD/GPL");

/* 模块被装载到内核时调用 */
static int hello_init(void)
{
    /* printk是内核自己的输出函数，因为内核在运行时不能
     * 依赖C库函数. */
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

/* 模块被移除时调用 */
static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
