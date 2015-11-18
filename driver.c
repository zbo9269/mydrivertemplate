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
