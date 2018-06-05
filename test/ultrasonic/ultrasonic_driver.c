#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/time.h>

#define TRIG 23
#define ECHO 24

MODULE_LICENSE("GPL");

static void sonic_read(void)
{
    struct timeval start_time, end_time;
    unsigned long start, end, travel;

    gpio_set_value(TRIG, 0);
    udelay(2);

    gpio_set_value(TRIG, 1);
    udelay(10);
    gpio_set_value(TRIG, 0);

    while(gpio_get_value(ECHO) == 0);
    do_gettimeofday(&start_time);

    while(gpio_get_value(ECHO) == 1);
    do_gettimeofday(&end_time);

    start = (unsigned long)start_time.tv_sec*1000000 + (unsigned long)start_time.tv_usec;
    end = (unsigned long)end_time.tv_sec*1000000 + (unsigned long)end_time.tv_usec;

    // is it microsecond? -> yes :)
    travel = end - start;

    printk("[TEST] start %lu / end %lu / travel %lu\n", start, end, travel);

    // cannot use floating point in kernel driver
    // -> distance = travel * 0.01715 (cm)
}

static int __init sonic_init(void)
{
    int i;

    gpio_request_one(TRIG, GPIOF_OUT_INIT_LOW, "TRIG");
    gpio_request_one(ECHO, GPIOF_IN, "ECHO");

    // test
    for(i=0; i<10; i++)
    {
        sonic_read();
        mdelay(1000);
    }

    return 0;
}

static void __exit sonic_exit(void)
{
    gpio_free(TRIG);
    gpio_free(ECHO);
}

module_init(sonic_init);
module_exit(sonic_exit);
