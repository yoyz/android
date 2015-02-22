# android

working with adb

root@yoyz-laptop:~/ lsusb 
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 004 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
Bus 005 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
Bus 006 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
Bus 001 Device 002: ID 058f:a001 Alcor Micro Corp. 
Bus 001 Device 033: ID 18d1:4e22 Google Inc. Nexus S (debug)

root@yoyz-laptop:~/ cat /etc/udev/rules.d/51-android.rules
SUBSYSTEM=="usb", SYSFS{idVendor}=="22b8", SYSFS{idProduct}=="708b", MODE="0666"

root@yoyz-laptop:~/ adb  kill-server

root@yoyz-laptop:~/ adb  start-server
* daemon not running. starting it now on port 5037 *
* daemon started successfully *


roott@yoyz-laptop:~/ adb shell
root@android:/ # 




Here is the SDL port 
https://github.com/pelya/commandergenius
