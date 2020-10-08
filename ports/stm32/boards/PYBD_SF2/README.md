# PYBD_SF2

## Pinout

| Signal     | CPU name | pin name |
| ---------- | -------- | -------- |
| BMP_SWDIO  | PA7      | X8       |
| BMP_SWCLK  | PA5      | X6       |
| BMP_SWO    | PA3      | X4       |
| BMP_SRST   | PA2      | X3       |
| BMP_TDI    | PC5      | X12      |
| BMP_PWR_EN | PF2      | X15      |

`BMP_PWR_EN` switches 3V3 power on pin X15 on and off.

The default dap calibration value is for the default cpu clock of 120 MHz. If changing cpu clock frequency, recalibrate SWD clock before using DAP. Typical values:

| cpu clock | dap.calibrate()  |
| --------- | ---------------- |
| 120MHz    | (20000,8000000)  |
| 216MHz    | (36000,14400000) |