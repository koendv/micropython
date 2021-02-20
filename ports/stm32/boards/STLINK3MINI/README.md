# stlink v3 mini

## jtag connector

| CN5 # | Pin      | Signal    | Notes                                    |
| ----- | -------- | --------- | ---------------------------------------- |
| 1     |          | 5V-supply | 5V power out. LED3 lit green if PB0 high |
| 2     | PA7      | SWDIR     | SWDIO level shifter direction            |
| 3     | PA0      | VTref     | target reference voltage, ADC1 channel 0 |
| 4     | PF9, PH7 | TMS_SWDIO | output/input                             |
| 5     | GND      |           |                                          |
| 6     | PB2, PH6 | TCK_SWCLK | output                                   |
| 7     | GND      |           |                                          |
| 8     | PB5, PC7, PD2 | TDO_SWO   | input                                    |
| 9     | PB2, PH6 | TCK_SWCLK | output                                   |
| 10    | PA1, PF8 | TDI       | output                                   |
| 11    | PG5      |           | ground detect                            |
| 12    | PA6      | nRESET    | output w/ pull-up                        |
| 13    | PG9      | RXD       | USART6_RX                                |
| 14    | PG14     | TXD       | USART6_TX                                |

Together, pin 3 to pin 12 form a MIPI10 connector.

## 32 pin edge connector

| CN2 # | CN5 # | Pin      | Signal                             | CN2 # | CN5 # | Pin      | Signal    |
| ----- | ----- | -------- | ---------------------------------- | ----- | ----- | -------- | --------- |
| 1     |       | PB11     | USART3_RX                          | 32    |       | PA7      |           |
| 2     |       | PD11     | USART3_CTS                         | 31    | 12    | PA6      | nRESET    |
| 3     |       | PD12     | USART3_RTS                         | 30    | 3     | PA0      | VTref     |
| 4     | 4     | PF9, PH7 | TMS_SWDIO (=SPI5_MOSI + SPI5_MISO) | 29    |       | GND      |           |
| 5     |       | PG5      |                                    | 28    | 10    | PA1, PF8 | TDI       |
| 6     | 6     | PB5, PC7, PD2      | TDO_SWO (=UART5_RX)      | 27    |       | GND      |           |
| 7     |       | PA9      |                                    | 26    |       | GND      |           |
| 8     |       | GND      |                                    | 25    |       | PC1      |           |
| 9     |       | PA11     | USB_FS_DM, CAN1_TX                 | 24    |       | GND      |           |
| 10    |       | PA12     | USB_FS_DP, CAN1_RX                 | 23    |       | PC2      |           |
| 11    |       | PC10     | USART3_TX                          | 22    |       | 5V-supply| CN5 pin #1|
| 12    | 14    | PG9      | USART6_RX                          | 21    |       | PE6      | SPI4_MOSI |
| 13    | 6     | PB2, PH6 | TCK_SWCLK (=SPI5_SCK)              | 20    |       | PE5      | SPI4_MISO |
| 14    |       | PB4      |                                    | 19    |       | PE4      | SPI4_NSS  |
| 15    | 13    | PG14     | USART6_TX                          | 18    |       | PE2      | SPI4_SCK  |
| 16    |       | PB8      | I2C1_SCL                           | 17    |       | PB9      | I2C1_SDA  |

## SWD connector

| #   |       | Pin  |
| --- | ----- | ---- |
| 1   | 3V3   |      |
| 2   | SWCLK | PA14 |
| 3   | GND   |      |
| 4   | SWDIO | PA13 |

## Other

| Pin  | Signal                   | Notes                               |
| ---- | ------------------------ | ----------------------------------- |
| PA10 | LED1                     | low: green, high: red, high-z: dark |
| PB0  | T_PWR_EN                 | LED3 green power on                 |
| LED2 | LED2 red when power fail |                                     |
| PB1  | T_PWR_EXT                | target power supply, ADC1 channel 9 |
| PI4  | HW_TYP_0                 | hardware id bit 0                   |
| PI5  | HW_TYP_1                 | hardware id bit 1                   |

## Compilation

### micropython

To compile micropython, clone the git repository, and type:

    cd micropython
    make -C mpy-cross
    make -C ports/stm32 submodules
    git submodule update --init lib/btstack
    make -C ports/stm32 BOARD=STLINK3MINI USER_C_MODULES=../../../extmod

The micropython firmware can be found in `micropython/ports/stm32/build-STLINK3MINI/firmware.*`.

### bootloader

To compile the bootloader:

    make -C ports/stm32/mboot BOARD=STLINK3MINI

The bootloader can be found in `micropython/ports/stm32/mboot/build-STLINK3MINI/firmware.*`

## Initial install

Upload the mboot bootloader and micropython over the SWD port, using a debugger. You may have to reset the option bytes first.

## Firmware upload

If micropython is running, booting in the DFU bootloader and uploading new firmware is easy. Connect to the micropython serial, and at the prompt, type:

    >>> import machine
    >>> machine.bootloader()

The system will reboot in DFU mode. If you run a `lsusb`, you should see:

     ID 0483:df11 STMicroelectronics STM Device in DFU Mode

Go to the firmware directory, and  upload the firmware with dfu-util:

    koen@raspberrypi:~/src/micropython/ports/stm32/build-STLINK3MINI$ sudo dfu-util -D firmware.dfu

Power cycle, and the system reboots in the new firmware.

## Schematic
The file ``stlink-v3-schematic.pdf`` in the ``docs/`` directory is the schematic of the stlink v3, as implemented on the nucleo board.
The file ``stlink3mini-schematic.pdf`` is what I *assume* the schematic of the stlink v3 mini to be.

## References

- [UM2502 User manual STLINK-V3MODS and STLINK-V3MINI](https://www.st.com/resource/en/user_manual/dm00555046-stlinkv3mods-and-stlinkv3mini-mini-debuggersprogrammers-for-stm32-stmicroelectronics.pdf), 9.c Connectors

- [RadioOperator](https://github.com/RadioOperator/CMSIS-DAP_for_STLINK-V3MINI/) port of CMSIS-DAP to stlink v3 mini 

- 3d-printable [box](https://www.st.com/resource/en/board_manufacturing_specification/stlink-v3mini_manufacturing.zip)
