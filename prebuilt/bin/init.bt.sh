#!/system/bin/sh
/system/bin/bt_downloader --baudrate 3000000 --patchram /system/etc/firmware/bcm4325.hcd /dev/ttyHS0

/system/bin/hciattach -s 3000000 /dev/ttyHS0 any 3000000 flow
