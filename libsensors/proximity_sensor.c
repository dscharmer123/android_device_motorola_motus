/**
 *Added for Morrison 02/09 tnbq73 
 *Feature ID 964  : Proximity Sensor  
 **/

#define LOG_TAG "PROXIMITY"
#define PROXIMITY_DEVICE "/sys/devices/platform/sfh7743.-2/proximity"
#define TOUCHPAD_DEVICE "/dev/touchpad"

/*Todo: need to include touchpad.h*/
#define KEY08_IOCTL_DISABLE 16
#define KEY08_IOCTL_ENABLE  17

#include <proximity_sensor.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static int send_command(int command)
{
    int nwr, ret, fd;
    char value[20];
    
    fd = open(PROXIMITY_DEVICE, O_RDWR);
    if(fd < 0)
        return errno;

    nwr = sprintf(value, "%d\n", command);
    ret = write(fd, value, nwr);

    close(fd);

    return (ret>=0) ? 0 : -1;
}

int proximity_on()
{
    return send_command(1);
}

int proximity_off()
{
    return send_command(0);
}

int touchpad_enable()
{
  int fd,ret;

  fd = open(TOUCHPAD_DEVICE, O_RDWR);
  if(fd < 0)
    return errno;

  ret = ioctl(fd, KEY08_IOCTL_ENABLE);
  close(fd);

  return (ret>=0) ? 0 : -1;
}

int touchpad_disable() 
{
  int fd,ret;

  fd = open(TOUCHPAD_DEVICE, O_RDWR);
  if(fd < 0)
    return errno;

  ret = ioctl(fd, KEY08_IOCTL_DISABLE);
  close(fd);

  return (ret>=0) ? 0 : -1;
}
