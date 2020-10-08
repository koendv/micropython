# DEVEBOX_STM32H743

## Installing bootloader

-   download and unzip firmware
-   disconnect board from USB
-   connect pin BOOT0 with pin 3V3
-   connect board to USB
-   install bootloader:

        sudo dfu-util -a 0 -d 0x0483:0xDF11 -D mboot/build-DEVEBOX_STM32H743/firmware.dfu

-   disconnect board from USB
-   remove connection between BOOT0 and 3V3
-   connect board to USB
-   run `dfu-util -l`. The device should appear.
-   from now on, you can boot in DFU mode by pressing button K2 during boot. 
-   when in mboot bootloader, LED blinks.

## Installing micropython

    sudo dfu-util -a 0 -d 0x0483:0xDF11 -D build-DEVEBOX_STM32H743/firmware.dfu

## DFU

-   you can boot in DFU mode by first connecting BOOT0 and 3V3, then connecting usb.

-   with mboot installed, you can also boot in DFU mode by pressing button K2 during boot. When in mboot bootloader, LED blinks.

-   with mboot and micropython installed, you can also boot in DFU mode by typing `machine.bootloader()` at the micropython prompt.

-   upgrade firmware over usb with `sudo dfu-util -a 0 -D firmware.dfu` or from the source tree with `sudo make -C ports/stm32 BOARD=DEVEBOX_STM32H750 USER_C_MODULES=../../../extmod deploy`

-   as a measure of last resort, you can boot in DFU mode by connecting BOOT0 and 3V3, connecting a usb-to-serial adapter to pins A9 and A10, and uploading firmware over DFU with the command `stm32flash`. You may need to compile `stm32flash` from source to get the latest version.

## SD card

The board does not have a "detect SD card present" pin. Manually write 0 to pyb.Pin.board.SD_SW to force pyb.SDCard().present() True.

    >>> import pyb
    >>> import os
    >>> pyb.SDCard().present()
    False
    >>> from machine import Pin
    >>> sd_sw = Pin(pyb.Pin.board.SD_SW, Pin.OUT)
    >>> sd_sw.value()
    0
    >>> pyb.SDCard().present()
    True
    >>> sd_sw.value(1)
    >>> pyb.SDCard().present()
    False
    >>> sd_sw.value(0)
    >>> pyb.SDCard().present()
    True
    >>> os.mount(pyb.SDCard(), '/sd')
    >>> os.listdir('/sd')
    ['bmp.py']

Put the SD card’s filesystem in the path list so Python scripts can be imported from the SD card.

    >>> import sys
    >>> sys.path
    ['', '/flash', '/flash/lib']
    >>> sys.path.append('/sd')
    >>> sys.path.append('/sd/lib')
    >>> sys.path
    ['', '/flash', '/flash/lib', '/sd', '/sd/lib']

The stm32h743 full speed usb supports only 2 virtual comm ports. (The stm32h743 has 2 FS USB ports, but only one is broken out to a usb connector)

## Target connections

Connect target SWD/JTAG pins to the connetor labeled "LCD/OLED":

| Pin | Signal | Note         |
| --- | ------ | ------------ |
| 1   | 3V3    | power        |
| 2   | GND    | ground       |
| 3   | PB15   | target SWDIO |
| 4   | PB13   | target SWCLK |
| 5   | PB12   | target TDI   |
| 6   | PB14   |              |
| 7   | PB1    | target SRST  |
| 8   | PB0    |              |
