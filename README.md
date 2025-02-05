LVGL EEZ Studio Boilerplate for ESP32-CYD 
=========================================

Boilerplate repository to start projects for ESP32 based on LVGL and EEZ-Studio.

This boilerplate project is based on a very cheap ESP32-CYD Hardware (ESP32 with 320x240 TFT Display and resistive touchscreen, SD card slot and GPIO): [Aliexpress Link for ESP32-CYD](https://it.aliexpress.com/item/1005006284129428.html)


But you can easily adapt to other esp32 board and display/touch changing PIN definition, `lv_conf.h and` and  `User_Setup.h` files.

> In order to avoid modification of `User_Setup.h` file inside the TFT_eSPI library (that can be overwritten updating the lib) is now possible to assign the same options using build_flag in the platformio.ini.


[EEZ-Studio](https://github.com/eez-open/studio) is used here to create LVGL interfaces using a great visual tool.


## Usage:

- Clone this repo and rename to application name.
- Open project with EEZ-Studio and build to generate ui files
- Open project with platformio (it will install all required libs under .pio/ directory). 
- Build and upload using platformio commands as usual
  
> Since the TFT_eSPI and LVGL libraries are based on HW specific configuration files, I include that files for ESP32-CYD board in `custom_files` directory. So you need to copy them in the relevant directories.

## Using and integrating EEZ-Studio:

LVGL C files are generate by EEZ-Studio under `src/ui/` directory.

You can use (optionally) EEZ-Flow logic engine in your EEZ-Studio project. In this case remember to uncomment the call to ui_tick() in your loop code.

## ESP32 Manual programming

```
esptool.py --chip esp32 --port "/dev/ttyUSB0" --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 4MB 0x1000 bootloader.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 firmware.bin
 ```


## TODO: 

- ~~add tips on how to use eez-studio with LVGL~~
- ~~looking for a way to use `lv_conf.h` and `User_Setup.h` without copy them in `.pio` subdir~~
- adapt the boilerplate for Raspberry Pi Pico (RP2040) too
- adapt the boilerplate for using LVGL PC simulation (?)
- ~~study EEZ-Studio Flows ~~

