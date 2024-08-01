LVGL EEZ Studio Boilerplate for ESP32-CYD 
=========================================

Boilerplate repository to start projects for ESP32 based on LVGL and EEZ-Studio.

This boilerplate project is based on a very cheap ESP32-CYD Hardware (ESP32 with 320x240 TFT Display and resistive touchscreen, SD card slot and GPIO): [Aliexpress Link for ESP32-CYD](https://it.aliexpress.com/item/1005006284129428.html)


But you can easily adapt to other esp32 board and display/touch changing PIN definition, `lv_conf.h and` and  `User_Setup.h` files.

## Usage:

- Clone this repo and rename to application name.
- Open project with platformio (it will install all required libs under .pio/ directory). 
- Copy `lv_conf.h` from `custom_files` directory to `.pio/libdeps/esp32dev/`
- Copy `User_Setup.h` from `custom_files` directory to `.pio/libdeps/esp32dev/TFT_eSPI/`

- Build and upload using platformio commands as usual
  
> Since the TFT_eSPI and LVGL libraries are based on HW specific configuration files, I include that files for ESP32-CYD board in `custom_files` directory. So you need to copy them in the relevant directories.

> TODO: searching for a way to use `lv_conf.h` and `User_Setup.h` without copy them in `.pio` subdir

## Using and integrating EEZ-Studio:

T.b.d.


## ESP32 Manual programming

```
esptool.py --chip esp32 --port "/dev/ttyUSB0" --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x1000 bootloader.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 firmware.bin
 ```
