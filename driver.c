#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/moduleparam.h> 
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#include "driver.h"

/*参数*/
static char *whom ="zhangb";
static int howmany =1;
module_param(whom,charp,S_IRUGO);
module_param(howmany,int,S_IRUGO);

/*获取设备号，并注册设备*/
static int getIndo(void)  
{
    int ret = -1;   
    dev_t dev = -1 ;
 
    if(major)
    {
       dev = MKDEV(major , 0);  
       ret = register_chrdev_region(dev,nr,"driver");  
    }  
    else
    {
        ret = alloc_chrdev_region(&dev,0,nr,"driver"); 
        major = MAJOR(dev);  
    }
    return ret ; 
} 

/*释放设备*/
static int clearIndo(void)
{
    unregister_chrdev_region(MKDEV(major , 0) ,nr);  
    return 0 ;
}

/*添加设备到系统*/
static void driver_setup_cdev(struct driver_dev *dev , int minor)
{
    int err ;
    dev_t devno = MKDEV(major , minor) ;
    
    cdev_init(&dev->cdev , &driver_ops);  
    dev->cdev.owner = THIS_MODULE ;
    err = cdev_add(&dev->cdev,devno,1);
    if (err) 
        printk(KERN_NOTICE "Error %d adding driver%d", err , minor);  
} 

/*从系统卸载设备*/  
static void driver_uninstall_cdev(struct driver_dev *dev)  
{
    cdev_del(dev);
}  

/*设备操作结构*/
struct file_operations driver_ops() = {
    .owner = THIS_MODULE,
    .read  = driver_read,
    .write  = driver_write,
    .ioctl  = driver_ioctl,
    .open  = driver_open,
    .release  = driver_release,
};


/*初始化设备*/
static int __init testinit(void)
{
    printk(KERN_ALERT "module init\n"); 
    getIndo();   

}

/*清除设备*/
static void __exit testexit(void)
{
    printk(KERN_ALERT "module exit\n");
    clearIndo();    
}

module_init(testinit);  
module_exit(testexit); 

/*说明*/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("zhangb"); 
MODULE_VERSION("v1.0");  
MODULE_DESCRIPTION("description"); 
