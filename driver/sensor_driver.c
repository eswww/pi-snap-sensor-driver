#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/cdev.h>
#include <linux/fcntl.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include <asm/uaccess.h>

#include "sensor_driver.h"

#define DEV_NAME "sensor_driver"

// Using GPIO pin number (Not a WiringPi pin number)

// Ultrasonic
#define TRIG 23
#define ECHO 24

// LED
#define R_LED 20
#define G_LED 21

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Device driver for ultrasonic sensor and LED");

static struct cdev *cd_cdev;
dev_t dev_num;

static unsigned long ultrasonic_read(void)
{
    struct timeval start_time, end_time;
    unsigned long start, end, travel;

    // Cannot use floating porint in kernel driver
    // distance = travel * 0.01715 or travel / 58 (cm)

    gpio_set_value(TRIG, 0);
    udelay(2);

    gpio_set_value(TRIG, 1);
    udelay(10);
    gpio_set_value(TRIG, 0);

    // Measuring execution time
    while(gpio_get_value(ECHO) == 0);
    do_gettimeofday(&start_time);

    while(gpio_get_value(ECHO) == 1);
    do_gettimeofday(&end_time);

    // Convert to microsecond
    start = (unsigned long)start_time.tv_sec*1000000 + (unsigned long)start_time.tv_usec;
    end = (unsigned long)end_time.tv_sec*1000000 + (unsigned long)end_time.tv_usec;
    travel = end - start;    // execution time (microsecond)

    return travel;
}

static int sensor_driver_open(struct inode *inode, struct file *file)
{
    printk("[SENSOR_DRIVER] Open\n");
    return 0;
}

static int sensor_driver_release(struct inode *inode, struct file *file)
{
    printk("[SENSOR_DRIVER] Release\n");
    return 0;
}

static long sensor_driver_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("[SENSOR_DRIVER] IOCTL\n");

    switch(cmd)
    {
        // Get sensor data
        case SENSOR_SONIC:
            return (long)ultrasonic_read();

        // Set Red LED
        case SENSOR_R_LED:
            gpio_set_value(G_LED, 0);
            gpio_set_value(R_LED, 1);
            break;

        // Set Green LED
        case SENSOR_G_LED:
            gpio_set_value(R_LED, 0);
            gpio_set_value(G_LED, 1);
            break;

        // Exit Application
        case SENSOR_CLOSE:
            gpio_set_value(R_LED, 0);
            gpio_set_value(G_LED, 0);

        default:
            return 0;
    }

    return 1;
}

struct file_operations sensor_driver_fops =
{
    .open = sensor_driver_open,
    .release = sensor_driver_release,
    .unlocked_ioctl = sensor_driver_ioctl
};

static int __init sensor_driver_init(void)
{
    printk("[SENSOR_DRIVER] Init\n");

    // Init dev
    cd_cdev = cdev_alloc();
    alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
    cdev_init(cd_cdev, &sensor_driver_fops);
    cdev_add(cd_cdev, dev_num, 1);

    // Init GPIO
    gpio_request_one(TRIG, GPIOF_OUT_INIT_LOW, "TRIG");
    gpio_request_one(ECHO, GPIOF_IN, "ECHO");
    gpio_request_one(R_LED, GPIOF_OUT_INIT_LOW, "R_LED");
    gpio_request_one(G_LED, GPIOF_OUT_INIT_LOW, "G_LED");

    return 0;
}

static void __exit sensor_driver_exit(void)
{
    printk("[SENSOR_DRIVER] Exit\n");

    // Free GPIO
    gpio_set_value(R_LED, 0);
    gpio_set_value(G_LED, 1);

    gpio_free(TRIG);
    gpio_free(ECHO);
    gpio_free(R_LED);
    gpio_free(G_LED);

    // Free dev
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
}

module_init(sensor_driver_init);
module_exit(sensor_driver_exit);
