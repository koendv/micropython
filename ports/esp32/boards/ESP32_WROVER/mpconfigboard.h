#define MICROPY_HW_BOARD_NAME "TTGO"
#define MICROPY_HW_MCU_NAME "ESP32_WROVER"

#define MODULE_BMP_ENABLED          (1)

#define BMP_SWDIO  27
#define BMP_SWCLK  26
#define BMP_SWO    22
#define BMP_SRST   25
#define BMP_TDI    33
#define BMP_TRST   21
#define BMP_SWDIR  18
#define BMP_PWR_EN 19
#define BMP_VTREF  35
#define BMP_LED     5

#define MODULE_FREEDAP_ENABLED      (1)
// default calibration values for this board
// after compilation, check with dap.calibrate() values are correct
#define DAP_DEFAULT_DELAY_CONSTANT  9600
#define DAP_DEFAULT_FAST_CLOCK      1500000

#define MICROPY_HW_LED1             (BMP_LED)
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_low(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_high(pin))
