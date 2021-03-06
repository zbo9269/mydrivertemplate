#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/moduleparam.h> 
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "driver.h"

/*参数*/
static char *whom ="zhangb";
static int howmany =1;
module_param(whom,charp,S_IRUGO);
module_param(howmany,int,S_IRUGO);

struct driver_dev driver_dev ;
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



int driver_open(struct inode *inode , struct file *filep)
{
    struct driver_dev *dev ;
    dev = container_of(inode->i_cdev,struct driver_dev, cdev); 
    filep->private_data = dev ; 
    return 0 ;
}

int driver_release(struct inode *inode , struct file *filep)
{
    //struct driver_dev *dev = filep->private_data ;
    return 0 ; 
}

ssize_t driver_write(struct file *filp , char __user *buf , size_t count , loff_t *fops) 
{
    return 1;
} 
/*设备操作结构*/
struct file_operations driver_ops = {
    .owner = THIS_MODULE,
    //.read  = driver_read,
    .write  = driver_write,
    //.ioctl  = driver_ioctl,
    .open  = driver_open,
    .release  = driver_release,
};

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
    cdev_del(&dev->cdev);
}  


/*初始化设备*/
static int __init testinit(void)
{
    printk(KERN_ALERT "module init\n"); 
    getIndo();  
    driver_setup_cdev(&driver_dev , 0);
 
    return 0 ;
}

/*清除设备*/
static void __exit testexit(void)
{
    printk(KERN_ALERT "module exit\n");
    driver_uninstall_cdev(&driver_dev) ; 
    clearIndo();    
}

module_init(testinit);  
module_exit(testexit); 

/*说明*/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("zhangb"); 
MODULE_VERSION("v1.0");  
MODULE_DESCRIPTION("description"); 
