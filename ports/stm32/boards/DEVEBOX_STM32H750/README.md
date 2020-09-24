## Note


According to the datasheet, the stm32h750 has 128kbyte internal flash. These processors are intended to run from cheap, slow external qspi flash.

Actual stm32h750 processors may contain 2mbyte flash. Or they may not. Only 128kbyte is guaranteed. Flash above 128k is not factory tested. You can check flash has been written correctly with the gdb ```compare-sections``` command.

This firmware assumes a stm32h750 with 2mbyte flash. If you are lucky, you can run this firmware.

## Installing bootloader
- compile bootloader:
```
make -C ports/stm32/mboot BOARD=DEVEBOX_STM32H750 clean
make -C ports/stm32/mboot BOARD=DEVEBOX_STM32H750
```
- disconnect board from USB
- connect pin BOOT0 with pin 3V3
- connect board to USB
- go to micropython directory
- install bootloader:
```
sudo make -C ports/stm32/mboot BOARD=DEVEBOX_STM32H750 deploy
```
- disconnect board from USB

## Installing micropython

- connection BOOT0 and 3V3
- connect to usb
- go to micropython directory
- run ``dfu-util -l``. The device should appear.
- install micropython:
```
sudo make -C ports/stm32 BOARD=DEVEBOX_STM32H750 deploy
```
- disconnect from usb
- remove connection between BOOT0 and 3V3
- reconnect to usb
- device should appear

## DFU
- mboot still has issues on this board.

- you can boot in DFU mode by first connecting BOOT0 and 3V3, then connecting usb.

- upgrade firmware over usb with 
```
cd micropython/ports/stm32/mboot/build-DEVEBOX_STM32H750
sudo dfu-util -a 0 -D firmware.dfu
cd micropython/ports/stm32/build-DEVEBOX_STM32H750
sudo dfu-util -a 0 -D firmware.dfu
```
or from the source tree with 
```
sudo make -C ports/stm32/mboot BOARD=DEVEBOX_STM32H750 deploy
sudo make -C ports/stm32 BOARD=DEVEBOX_STM32H750 deploy
```

- as a measure of last resort, you can boot in DFU mode by connecting BOOT0 and 3V3, connecting a usb-to-serial adapter to pins A9 and A10, and uploading firmware over DFU with the ``stm32flash`` command. You may need to compile ``stm32flash`` from source to get the latest version.

- because of the nature of the port, few guarantees can be given.

## SD card
The board does not have a "detect SD card present" pin. Manually write 0 to pyb.Pin.board.SD_SW to force pyb.SDCard().present() True.


```
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
```
Put the SD card’s filesystem in the path list so Python scripts can be imported from the SD card.
```
>>> import sys
>>> sys.path
['', '/flash', '/flash/lib']
>>> sys.path.append('/sd')
>>> sys.path.append('/sd/lib')
>>> sys.path
['', '/flash', '/flash/lib', '/sd', '/sd/lib']
```

The stm32h750 full speed usb supports only 2 virtual comm ports. (The stm32h750 has 2 FS USB ports, but only one is broken out to a usb connector)

## Target connections

Connect target SWD/JTAG pins to the connetor labeled "LCD/OLED":

Pin | Signal | Note
---|---|---
1 | 3V3  | power
2 | GND  | ground
3 | PB15 | target SWDIO
4 | PB13 | target SWCLK
5 | PB12 | target TDI
6 | PB14 |
7 | PB1  | target SRST
8 | PB0  |
