#ifndef _HELLO_ANDROID_H_  
#define _HELLO_ANDROID_H_  
  
#include <linux/cdev.h>  
#include <linux/semaphore.h>  
#define DEVICE_NAME "liu"
#define HELLO_DEVICE_NODE_NAME  "hello"  
#define HELLO_DEVICE_FILE_NAME  "hello"  
#define HELLO_DEVICE_PROC_NAME  "hello"  
#define HELLO_DEVICE_CLASS_NAME "hello"  
 
#define mem_size 200

struct liu_dev {  
    unsigned char mem[mem_size];  
    struct semaphore sem;  
    struct cdev dev;  
};  
  
#endif  
