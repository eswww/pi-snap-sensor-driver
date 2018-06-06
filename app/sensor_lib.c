#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#include "sensor_lib.h"

int exit_application(void)
{
    int dev;
    dev = open("/dev/sensor_driver", O_RDWR);

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
    {
        ioctl(dev, SENSOR_G_LED, 0);
        return ENOUGH;
    }
    // It's not enough distance
    else
    {
        ioctl(dev, SENSOR_R_LED, 0);
        return NOT_ENOUGH;
    }
}
