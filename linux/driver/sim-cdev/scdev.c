#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

/* 告诉内核该模块使用自由许可证 */
MODULE_LICENSE("Dual BSD/GPL");

ssize_t scdev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
ssize_t scdev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_ops);

int scdev_major = 0;
int scdev_minor = 0;

static char data[512] = {0};

struct file_operations scdev_fops = {
    .owner = THIS_MODULE,
    .read = scdev_read,
    .write = scdev_write,
    .open = NULL,
    .release = NULL,
};

struct cdev *my_cdev;

/* 模块被装载到内核时调用 */
static int scdev_init(void)
{
    dev_t dev = 0;
    int result, err;
    /* printk是内核自己的输出函数，因为内核在运行时不能
     * 依赖C库函数. */
    /* printk(KERN_ALERT "Scdev, world\n"); */
    if (scdev_major) {
        dev = MKDEV(scdev_major, scdev_minor);
        result = register_chrdev_region(dev, 1, "sim_cdev");
    }
    else {
        result = alloc_chrdev_region(&dev, scdev_minor, 1, "sim_cdev");
        scdev_major = MAJOR(dev);
    }
    if (result < 0) {
        printk(KERN_WARNING "scdev: can not get major %d\n", scdev_major);
        return result;
    }

    memset(data, 0, 512);
    my_cdev = cdev_alloc();
    my_cdev->ops = &scdev_fops;
    my_cdev->owner = THIS_MODULE;
    err = cdev_add(my_cdev, dev, 1);
    if (err) {
        printk(KERN_WARNING "Error %d add simple cdev", err);
        return err;
    }
    printk(KERN_INFO "simple cdev initialized.\n");
    return 0;
}

ssize_t scdev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    if(copy_to_user(buf, data, 512)) {
        return -EFAULT;
    }
    else
        return strlen(data);
}

ssize_t scdev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_ops)
{
    if (copy_from_user(data, buf, 512)){
        return -EFAULT;
    }
    else
        return strlen(buf);
}

/* 模块被移除时调用 */
static void scdev_exit(void)
{
    cdev_del(my_cdev);
    printk(KERN_ALERT "simple cdev driver removed!\n");
}

module_init(scdev_init);
module_exit(scdev_exit);
