 #include <linux/gpio.h> 
 #include <linux/fs.h>
 #include <linux/cdev.h>
 #include <linux/device.h>
 #include <linux/uaccess.h>
 #include <linux/module.h>

 static dev_t devno;
 static struct class *SW2_class;
 static struct cdev SW2_cdev;
 struct file_operations SW2_fops;

 const int first_minor = 0;
 const int max_devices = 255;

int mygpio_open(struct inode *inode, struct file *filep)
{
    int major, minor;
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);
    printk("Opening MyGpio Device [major], [minor]: %i, %i\n", major, minor);
    return 0;
}

int mygpio_release(struct inode *inode, struct file *filep)
{
    int minor, major;
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);
    printk("Closing/Releasing MyGpio Device [major], [minor]: %i, %i\n", major, minor);
    return 0;
}

ssize_t mygpio_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
    // Hvilke trin er det der skal udføres?
    // Hint konvertering fra int til string kan gøres via sprintf() - Tekststrenge frem for binære værdier gør det nemmere at læse værdien i user-space med f.eks. cat.
    char kbuf[12];
    int len, value;
    value = gpio_get_value(16);
    len = count < 12 ? count : 12;
    len = snprintf(kbuf, len, "%i", value);
    if (copy_to_user(buf, kbuf, ++len)) return 0;
    *f_pos += len;
    return len;    
}


struct file_operations SW2_fops = {
    .owner      =   THIS_MODULE,
    .open       =   mygpio_open,
    .release    =   mygpio_release,
    .read       =   mygpio_read,
};

static int __init mygpio_init(void){
    int err=0;
    if (gpio_request(16, "gpio16") != 0){
        pr_info("gpio16 not found");
    }
    gpio_direction_input(16);
    err = alloc_chrdev_region(&devno, first_minor, max_devices, "hello-driver");
    if (MAJOR(devno) <= 0)
        pr_err("Failed to register chardev\n");
    
    pr_info("SW2 driver got Major %i\n", MAJOR(devno));

    SW2_class = class_create(THIS_MODULE, "SW2-class");
    if (IS_ERR(SW2_class)) pr_err("Failed to create class");

    cdev_init(&SW2_cdev, &SW2_fops);
    err = cdev_add(&SW2_cdev, devno, 255);
    if (err) pr_err("Failed to add cdev");
    return err;
 }

 static void __exit mygpio_exit(void){
    cdev_del(&SW2_cdev);
    class_destroy(SW2_class);
    unregister_chrdev_region(first_minor, max_devices);
    gpio_free(16);
 }



 module_init(mygpio_init);
 module_exit(mygpio_exit);
 MODULE_AUTHOR("Oliver B. Rosenkilde");
 MODULE_LICENSE("GPL");