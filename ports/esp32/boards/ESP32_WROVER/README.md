# ESP32

TTGO T8 v1.8 

- esp32-wrover
- 4 mbyte flash
- 8 mbyte ram
- sdcard 

## Use

Connect to console with ```picocom -b 115200 /dev/ttyUSB0``` or similar. 

Connect target as follows:

Signal|Pin
------|---
SWDIO | 27
SWCLK | 26
SWO   | 22
SRST  | 25

### IP
Start wifi. For a bmp gdb server on tcp port 3333, type:
 
```
bmp.init(tcp=3333)
```
### Serial

For a gdb server on serial port 1, on pins 22 and 23, at 115200 baud, type: 
```
gdb_uart=machine.UART(1,115200,rx=22,tx=23)
bmp.init(stream=gdb_uart)
```

## pinout

pin | function
---|---
0|
1|uart0 txd (to usb-serial adapter)
2|sdcard d0
3|uart0 rxd (from usb-serial adapter)
4|sdcard d1
5|LED, active low
9|uart1 rxd, BMP_SWO
10|uart1 txd
12|sdcard d2, esp32 tmi
13|sdcard d3, esp32 tck
14|sdcard clk, esp32 tms
15|sdcard cmd, esp32 tdo
18|BMP_SWDIR
19|BMP_PWR_EN
21|BMP_TRST
22|
23|
25|BMP_SRST
26|BMP_SWCLK
27|BMP_SWDIO
32|
33|BMP_TDI
34|analog input, VBAT/2 ? XXX 35
35|high if charging/ ? XXX
36|
39|

# Note
Before compiling, check the LED pin in mpconfigboard.h (BMP_LED) is correct.

Compile with 
```
cd micropython/ports/esp32
make BOARD=ESP32_WROVER USER_C_MODULES=../../../extmod/
```

[aliexpress](https://www.aliexpress.com/item/4001049714726.html)