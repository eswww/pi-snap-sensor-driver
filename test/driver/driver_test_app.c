#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#include "sensor_driver.h"

int exit_application(void);
unsigned long get_sensor_data(void);
int set_led(int sensor_data, int min, int max);

int exit_application(void)
{
    int dev;
    dev = open("/dev/sensor_drive", O_RDWR);

    // Device open error
    if(dev < 0)
        return -1;

    ioctl(dev, SENSOR_CLOSE, 0);

    close(dev);
    return 0;
}

unsigned long get_sensor_data(void)
{
    int dev;
    unsigned long sensor_data;

    dev = open("/dev/sensor_driver", O_RDWR);

    // Device open error
    if(dev < 0)
        return -1;

    sensor_data = (unsigned long)ioctl(dev, SENSOR_SONIC, 0);
    //printf("Sensor data: %lu\n", sensor_data);

    close(dev);
    return sensor_data;
}

int set_led(int sensor_data, int min, int max)
{
    int dev;
    dev = open("/dev/sensor_driver", O_RDWR);

    // Device open error
    if(dev < 0)
        return -1;

    // It's enough distance
    if(sensor_data > min && sensor_data < max)
        ioctl(dev, SENSOR_G_LED, 0);
    // It's not enough distance
    else
        ioctl(dev, SENSOR_R_LED, 0);

    return 0;
}

int main(void)
{
    int i;
    unsigned long sensor_data = 0;

    for(i=0; i<10; i++)
    {
        sensor_data = get_sensor_data();
        set_led(sensor_data, 500, 1000);
        sleep(3);
    }

    return 0;
}
