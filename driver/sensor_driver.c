#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>

#define DEV_NAME "sensor_driver"

// Ultrasonic
#define ECHO 8    // GPIO Pin Number (Not a WiringPi Pin Number)
#define TRIG 11

// LED
#define R_LED 23
#define G_LED 24

MODULE_LICENSE("GPL");

/*
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

struct file_operations sensor_driver_fops =
{
    .open = sensor_driver_open,
    .release = sensor_driver_release
};
*/

static int __init sensor_driver_init(void)
{
    printk("[SENSOR_DRIVER] Init\n");

    // Init GPIO
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
    gpio_free(R_LED);
    gpio_free(G_LED);
}

module_init(sensor_driver_init);
module_exit(sensor_driver_exit);
