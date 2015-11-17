#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/moduleparam.h> 
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#include "driver.h"

static char *whom ="zhangb";
static int howmany =1;
module_param(whom,charp,S_IRUGO);
module_param(howmany,int,S_IRUGO);

int nr = 3 ;
static int getIndo(dev_t major)  
{
    int rt = -1;   
    dev_t dev = -1 ;
 
    if(major)
    {
       dev = MKDEV(major , 0);  
       rt = register_chrdev_region(dev,nr,"driver");  
    }  
    else
    {
        rt = alloc_chrdev_region(&dev,0,nr,"driver"); 
        major = MAJOR(dev);  
    }
    return rt ; 
} 

static int clearIndo(dev_t major)
{
    unregister_chrdev_region(MKDEV(major , 0) ,nr);  
}

static int __init testinit(void)
{
    printk(KERN_ALERT "module init\n"); 
    getIndo(major);   
}

static void __exit testexit(void)
{
    printk(KERN_ALERT "module exit\n");
    clearIndo(major);    
}

module_init(testinit);  
module_exit(testexit); 

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("zhangb"); 
MODULE_VERSION("v1.0");  
MODULE_DESCRIPTION("description"); 
