#include <hardware_legacy/led.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define LOG_TAG "LED"
#include <utils/Log.h>

#if 0
const char* const AMBER_BLINK_FILE = "/sys/class/leds/amber/blink";
const char* const RED_BLINK_FILE = "/sys/class/leds/red/blink";
const char* const GREEN_BLINK_FILE = "/sys/class/leds/green/blink";
const char* const BLUE_BLINK_FILE = "/sys/class/leds/blue/blink";
#endif
const char* const BLINK_FILE = "/sys/class/leds/messaging/blink";

static int
write_string(const char* file, const char* string, int len)
{
    int fd;
    ssize_t amt;

    fd = open(file, O_RDWR);
    if (fd < 0) {
        LOGE("unable to open %s: %d\n", file, errno);
        return errno;
    }

    amt = write(fd, string, len);
    if (amt < 0) {
        LOGE("unable to write to %s: %d\n", file, errno);
    }

    close(fd);
    return amt >= 0 ? 0 : errno;
}

int morrison_set_led_state(unsigned colorARGB, int onMS, int offMS)
{
    int len;
    char buf[60];
    unsigned brightness = 0;
    
    LOGI("set_led_state colorARGB=%08X, onMS=%d, offMS=%d\n", colorARGB, onMS, offMS);
    
    // alpha of 0 or color of 0 means off
    if ((colorARGB & 0xff000000) == 0 || (colorARGB & 0x00ffffff) == 0) {
        onMS = 0;
        offMS = 0;
    }

    if (colorARGB & 0x00ffffff)
        brightness = 255;

    /* The driver accepts the following format for blinking:
     * <brightness> <onMs> <offMs>
     * If <brightness> is not 0 and onMs = offMs = 0 then
     * it will just be solid;
     * If <brightness> is 0 it will be off refardless of onMs and offMs
     * brightness files can be used too to just set it to solid or off
     */
    len = sprintf(buf, "%d %d %d", brightness, onMS, offMS);
    write_string(BLINK_FILE, buf, len);

    return 0;
}

int set_led_state2(unsigned colorARGB, int onMS, int offMS, 
    int onMS1, int offMS1)
{
    int len;
    char buf[60];
    unsigned brightness = 0;
    
    LOGI("set_led_state colorARGB=%08X, onMS=%d, offMS=%d\n", colorARGB, onMS, offMS);
    
    // alpha of 0 or color of 0 means off
    if ((colorARGB & 0xff000000) == 0 || (colorARGB & 0x00ffffff) == 0) {
        onMS = 0;
        offMS = 0;
        onMS1 = 0;
        offMS1 = 0;
    }

    if (colorARGB & 0x00ffffff)
        brightness = 255;

    /* The driver accepts the following format for blinking:
     * <brightness> <onMs> <offMs>
     * If <brightness> is not 0 and onMs = offMs = 0 then
     * it will just be solid;
     * If <brightness> is 0 it will be off refardless of onMs and offMs
     * brightness files can be used too to just set it to solid or off
     */
    len = sprintf(buf, "%d %d %d %d %d", 
        brightness, onMS, offMS, onMS1, offMS1);
    write_string(BLINK_FILE, buf, len);

    return 0;
}

/* Set two pulses with ramps.  Ramps are in percent of onMS, not in ms! */
int set_led_state2_ramp(unsigned colorARGB, int onMS, int offMS, 
    int onMS1, int offMS1, int ramp_up, int ramp_down, int ramp_up1,
    int ramp_down1)
{
    int len;
    char buf[60];
    unsigned brightness = 0;
    
    LOGI("set_led_state colorARGB=%08X, onMS=%d, offMS=%d\n", colorARGB, onMS, offMS);
    
    // alpha of 0 or color of 0 means off
    if ((colorARGB & 0xff000000) == 0 || (colorARGB & 0x00ffffff) == 0) {
        onMS = 0;
        offMS = 0;
        onMS1 = 0;
        offMS1 = 0;
    }

    if (colorARGB & 0x00ffffff)
        brightness = 255;

    /* The driver accepts the following format for blinking:
     * <brightness> <onMs> <offMs> <onMs1> <offMs1> ramp <ru> <rd> <ru1> rd1>
     * If <brightness> is not 0 and onMs = offMs = 0 then
     * it will just be solid;
     * If <brightness> is 0 it will be off refardless of onMs and offMs
     * brightness files can be used too to just set it to solid or off
     */
    if (ramp_up == -1 && ramp_down == -1 && ramp_up1 == -1 &&
        ramp_down1 == -1) {
        len = sprintf(buf, "%d %d %d %d %d", 
            brightness, onMS, offMS, onMS1, offMS1);
    } else {
        len = sprintf(buf, "%d %d %d %d %d ramp %d %d %d %d", 
            brightness, onMS, offMS, onMS1, offMS1, ramp_up, ramp_down,
            ramp_up1, ramp_down1);
    }
    write_string(BLINK_FILE, buf, len);

    return 0;
}
