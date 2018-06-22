# pi-snap-sensor-driver

## Introduction

Project for `pi-snap` sensor driver

## Parts list

- Ultrasonic sensor
- Red LED
- Green LED

## Kernel directory path

```
~/linux-rpi
```

## How to use

### 1. Build

**../pi-snap-sensor-driver/driver/**

```bash
$ make
```

**../pi-snap-sensor-driver/app/**

```bash
$ make
```

### 2. Load device driver

**../pi-snap-sensor-driver/driver/**

```bash
$ insmod sensor_driver.ko
$ sh mknod.sh
```

### 3. Modify IP address

#### ../pi-snap-sensor-driver/app/sensor_lib.h

```c
...
#define IP "127.0.0.1"    // Here!
...
```

### 4. Run application

_Before running an application, you must ensure that the socket server is running!_

```bash
$ ./sensor_app.out
```
