/*hello_evdev*/

#include<linux/device.h>
#include<linux/input.h>
#include<linux/module.h>

#define evdev_debug 

struct input_dev *my_dev;

static int __init hello_evdev_init(void){
	
	int err = -1;
	
	ifdef evdev_debug
	printk(KERN_ALERT"%s.\n", __fun__); 
	endif
	
	my_dev = input_allocate_device();//使用input的专有函数分配空间，创建设备
	if(NULL == my_dev){
		 printk(KERN_ALERT"Failed to allocate hello_evdev %d.\n"); 
		 goto err_input_dev_alloc_failed;
	}
	my_dev->name = "hello_evdev";
	
	//申明设备类型
	set_bit(EV_SYN, my_dev->evbit);
	set_bit(EV_KEY, my_dev->evbit);
	
	err = input_register_device(my_dev);
	if(err){
		printk(KERN_ALERT"Failed to register hello_evdev %d.\n"); 
		goto err_input_dev_register_failed;
	}
	
	/*err = alloc_chrdev_region(&dev, 0, 1, my_dev->name);  
    if(err < 0) {  
    printk(KERN_ALERT"Failed to alloc char dev region.\n");  
    goto fail;  
    }  */
		
    /*在/dev/目录下创建设备文件hello_evdev  
	temp = device_create(input_class, NULL, , "%s", my_dev->name);  
    if(IS_ERR(temp)) {  
        err = PTR_ERR(temp);  
        printk(KERN_ALERT"Failed to create hello device.");  
        goto destroy_class;  
    }   */
	
	
	err_input_dev_alloc_failed:
	err_input_dev_register_failed:
		input_free_device(my_dev);
	
	ifdef evdev_debug
	printk(KERN_ALERT"%s return err=%d.\n", __fun__, err); 
	endif
	
		return err;
		
}





static int __exit hello_evdev_exit(){
	
	ifdef evdev_debug
	printk(KERN_ALERT"%s.\n", __fun__); 
	endif
	
	input_unregister_device(my_dev);
	return 0;	
}



MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("First Android Driver");     
module_init(hello_evdev_init);  
module_exit(hello_evdev_exit); 