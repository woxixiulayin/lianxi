//#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/proc_fs.h>  
#include <linux/device.h>  
#include <asm/uaccess.h>  
#include <linux/semaphore.h>
#include "hello.h"  
  
static struct liu_dev* liudev = NULL;
static struct class* liu_class = NULL;

static int liu_major = 0;
static int liu_minor = 0;

struct file_operations liu_ops;
static int liu_dev_setup(struct liu_dev* dev)
{
	int err;
	dev_t devno = MKDEV(liu_major,liu_minor);
	memset(dev, 0, sizeof(struct liu_dev));
	
	//字符设备初始化
	cdev_init(&(dev->dev), &liu_ops);
	dev->dev.owner = THIS_MODULE;
	//可以不要？
	dev->dev.ops = &liu_ops;
	
	//注册字符设备
	err = cdev_add(&(dev->dev), devno, 1);
	if(err){
		return err;
	}
	
	//初始化信号量和寄存器的值;
	sema_init(&(dev->sem), 1);
	strcpy(dev->mem, "dev_liu");
	return 0;
}

/*创建/proc/liu文件  
static void liu_create_proc(void) {  
    struct proc_dir_entry* entry;  
      
    entry = create_proc_entry(DEVICE_NAME, 0, NULL);  
    if(entry) {  
        entry->owner = THIS_MODULE;  
        entry->read_proc = liu_proc_read;  
        entry->write_proc = liu_proc_write;  
    }  
}*/

//设备读函数
static ssize_t liu_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	ssize_t ret  = 0;
	unsigned int count = size;
	unsigned long p = *ppos;
	
	if(down_interruptible(&(liudev->sem)))
	{
		return -ERESTARTSYS;
	}
	
	//要读的偏移位置越界
	if(p >= mem_size) 
		return 0;

	//要读的字节数太大
	if(count > mem_size - p)
		count = mem_size - p;
		
	if(copy_to_user(buf, (void *)(liudev->mem + p), count))
		ret  = -EFAULT;
	else {
		*ppos += count;
		ret = count;
		printk(KERN_ALERT"read %d bytes from %d\n", count, p);
	     }

	up(&(liudev->sem));
	return ret;
}

//设备写函数
static ssize_t liu_write(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{	
	ssize_t ret = 0;
	unsigned int count = size;
	unsigned long p = *ppos;

	if(down_interruptible(&(liudev->sem))) return -ERESTARTSYS;
	
	if(p >= mem_size) return 0;
	if(count > mem_size - p)
		count = mem_size - p;

	if(copy_from_user(liudev->mem + p, buf, count))
		ret = -EFAULT;
	else {
		*ppos += count;
		ret  = count;
		printk(KERN_ALERT"written %d bytes from %d\n", count, p);
	}
	
	up(&(liudev->sem));
	return ret;
}


struct file_operations liu_ops = {
	.owner = THIS_MODULE,
//	.open = liu_open,
	.read = liu_read,
       	.write = liu_write,

};

static int __init liu_init(void)
{
	int err;
	struct device* temp = NULL;  	
	dev_t devno = MKDEV(liu_major, liu_minor);
	//动态申请设备号
	err = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
		
	printk(KERN_ALERT"Creat liu  device.\n");    
	
	liu_major = MAJOR(devno);
	liu_minor = MINOR(devno);
	
	//申请结构提变量空间
	liudev = kmalloc(sizeof(struct liu_dev), GFP_KERNEL);  
	if(!liudev){
		printk(KERN_ALERT"faile to alloc liu dev");
		return 1;
	}
	
	err = liu_dev_setup(liudev);
	
	liu_class = class_create(THIS_MODULE, DEVICE_NAME);
	temp = device_create(liu_class, NULL, devno, "%s", DEVICE_NAME);
	//err = device_create_file(temp, );

	return 0;
}

static void __exit liu_exit(void)
{
	dev_t devno = MKDEV(liu_major, liu_minor);
	
	printk(KERN_ALERT"begin Destroy liu device.\n");    

	device_destroy(liu_class, devno);
	class_destroy(liu_class);

	//删除字符设备
	cdev_del(&(liudev->dev));
	
	//释放设备内存
	kfree(liudev);
	
	//释放设备号
	unregister_chrdev_region(devno, 1);
	printk(KERN_ALERT"Destroy liu device ok.\n");    
	
}

MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("First Android Driver");  
  
module_init(liu_init);  
module_exit(liu_exit); 

