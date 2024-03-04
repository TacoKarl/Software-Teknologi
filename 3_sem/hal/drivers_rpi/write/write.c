 #include <linux/gpio.h> 
 #include <linux/fs.h>
 #include <linux/cdev.h>
 #include <linux/device.h>
 #include <linux/uaccess.h>
 #include <linux/module.h>

 static dev_t devno;
 static struct class *LED3_class;
 static struct cdev LED3_cdev;
 struct file_operations LED3_fops;

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

ssize_t mygpio_write(struct file *filep, const char __user *ubuf, size_t count, loff_t *f_pos)
{
    // Hvilke trin er det der skal udføres?
    // Hint konvertering fra string til int kan gøres via sscanf() - antagelsen er at det er strenge der sendes til og fra user space.  
    int len, value, err = 0;
    char kbuf[12];
    len = count < 12 ? count : 12;
    err = copy_from_user(kbuf, ubuf, len);
    if (err < 0)
        return -EFAULT;
    
    if (sscanf(kbuf, "%i", &value))
        pr_err("Error converting string to int\n");

    gpio_set_value(26, value);

    
    pr_info("Wrote %i from mino %i\n", value, iminor(filep->f_inode));
    *f_pos += len;
    return len;
}

ssize_t mygpio_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
    // Hvilke trin er det der skal udføres?
    // Hint konvertering fra int til string kan gøres via sprintf() - Tekststrenge frem for binære værdier gør det nemmere at læse værdien i user-space med f.eks. cat.
    char kbuf[12];
    int len, value;
    value = gpio_get_value(16);

    if (gpio_get_value(16))
        gpio_set_value(26, 0);
    else 
        gpio_set_value(26, 1);
    len = count < 12 ? count : 12;
    len = snprintf(kbuf, len, "%i", value);
    if (copy_to_user(buf, kbuf, ++len)) return 0;
    *f_pos += len;
    return len;    
}

struct file_operations LED3_fops = {
    .owner      =   THIS_MODULE,
    .open       =   mygpio_open,
    .release    =   mygpio_release,
    .write      =   mygpio_write,
    .read       =   mygpio_read
};

static int __init mygpio_init(void){
    int err=0;
    if (gpio_request(26, "gpio26") != 0){
        pr_info("gpio26 not found");
    }
    gpio_direction_input(16);
    gpio_direction_output(26, 1);
    err = alloc_chrdev_region(&devno, first_minor, max_devices, "hello-driver");
    if (MAJOR(devno) <= 0)
        pr_err("Failed to register chardev\n");
    
    pr_info("LED3 driver got Major %i\n", MAJOR(devno));

    LED3_class = class_create(THIS_MODULE, "LED3-class");
    if (IS_ERR(LED3_class)) pr_err("Failed to create class");

    cdev_init(&LED3_cdev, &LED3_fops);
    err = cdev_add(&LED3_cdev, devno, 255);
    if (err) pr_err("Failed to add cdev");
    return err;
 }

 static void __exit mygpio_exit(void){
    cdev_del(&LED3_cdev);
    class_destroy(LED3_class);
    unregister_chrdev_region(first_minor, max_devices);
    gpio_free(26);
    gpio_free(16);
 }



 module_init(mygpio_init);
 module_exit(mygpio_exit);
 MODULE_AUTHOR("Oliver B. Rosenkilde");
 MODULE_LICENSE("GPL");

 //insmod *write.ko
 //dmesg
 //mknod /dev/<name> c <MAJOR> <MINOR>
 //cat /dev/<NAME>
 //echo 1 > /dev/<NAME>
 //rmmod