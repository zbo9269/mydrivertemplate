#include <linux/types.h> 
//设备个数
int nr = 4;
//主设备号
dev_t major = 0 ; 

//设备结构
struct driver_dev 
{
    struct cdev cdev ;   
};     
