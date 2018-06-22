#ifndef __SENSOR_LIB_H__
#define __SENSOR_LIB_H__

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2
#define IOCTL_NUM3 IOCTL_START_NUM+3
#define IOCTL_NUM4 IOCTL_START_NUM+4
 
#define SENSOR_IOCTL_NUM 'z'
#define SENSOR_SONIC _IOWR(SENSOR_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define SENSOR_R_LED _IOWR(SENSOR_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define SENSOR_G_LED _IOWR(SENSOR_IOCTL_NUM, IOCTL_NUM3, unsigned long *)
#define SENSOR_CLOSE _IOWR(SENSOR_IOCTL_NUM, IOCTL_NUM4, unsigned long *)

#define PORT 2324
#define IP "169.254.152.157"

#define ENOUGH 1
#define NOT_ENOUGH 0

int exit_application(void);
unsigned long get_sensor_data(void);
int set_led(int sensor_data, int min, int max);

#endif
