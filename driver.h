#include <linux/types.h> 
//设备个数
int nr = 4;
//主设备号
dev_t major = 0 ; 

struct driver_dev 
{
    struct cdev cdev ;   
};     
