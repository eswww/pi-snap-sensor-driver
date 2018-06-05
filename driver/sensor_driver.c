#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>

#define DEV_NAME "sensor_driver"

// Using GPIO pin number (Not a WiringPi pin number)

// Ultrasonic
#define TRIG 23
#define ECHO 24

// LED
#define R_LED 20
#define G_LED 21

MODULE_LICENSE("GPL");

static int ultrasonic_read(void)
{
    struct timeval start_time, end_time;
    unsigned long start, end, travel;

    // Cannot use floating point in kernel driver
    // distance = travel * 0.01715 (cm)

    gpio_set_value(TRIG, 0);
    udelay(2);

    gpio_set_value(TRIG, 1);
    udelay(10);
    gpio_set_value(TRIG, 0);

    // Measuring excution time
    while(gpio_get_value(ECHO) == 0);
    do_gettimeofday(&start_time);

    while(gpio_get_value(ECHO == 1));
    do_gettimeofday(&end_time);

    start = (unsigned long)start_time.tv_sec*1000000 + (unsigned long)start_time.tv_usec;
    end = (unsigned long)end_time.tv_sec*1000000 + (unsigned long)end_time.tv_usec;

    travel = end - start;    // microsecond
    return travel;
}

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
}

module_init(sensor_driver_init);
module_exit(sensor_driver_exit);
