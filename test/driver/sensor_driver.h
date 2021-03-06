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
