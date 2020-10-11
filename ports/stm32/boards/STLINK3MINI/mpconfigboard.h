/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define MICROPY_HW_BOARD_NAME       "stlink3mini"
#define MICROPY_HW_MCU_NAME         "stm32f723iek"

#define MICROPY_PY_PYB_LEGACY       (0)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
#define MICROPY_HW_HAS_SWITCH       (0)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SERVO     (0)
#define MICROPY_HW_ENABLE_DAC       (0)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SDCARD    (0)
#define MICROPY_HW_ENABLE_MMCARD    (0)

// Settings for 216 MHz.
// Values from stm32cubemx clock configuration.
// HSE external crystal is 25MHz
// VCOClock = HSE * PLLN / PLLM = 25 MHz * 432 / 25 = 432 MHz
// SYSCLK = VCOClock / PLLP = 432 MHz / 2 = 216 MHz
// USB/SDMMC/RNG Clock = VCOClock / PLLQ = 432 MHz / 9 = 48 MHz
// Note: no external sdram on bmp, sdram requires SYSCLK <= 200MHz
#define MICROPY_HW_CLK_PLLM (25)
#define MICROPY_HW_CLK_PLLN (432)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV2)
#define MICROPY_HW_CLK_PLLQ (9)

// See reference manual: cpu clock 216 MHz -> 7 wait states
// From cubemx -> Pinout & Configuration -> System Core -> RCC -> Parameter Settings -> System Parameters -> Flash Latency
#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_7

// UART config
#define MICROPY_HW_UART3_TX         (pin_C10)
#define MICROPY_HW_UART3_RX         (pin_B11)
#define MICROPY_HW_UART3_RTS        (pin_D12)
#define MICROPY_HW_UART3_CTS        (pin_D11)

#define MICROPY_HW_UART5_TX         (pin_D2)
#define MICROPY_HW_UART5_RX         (pin_C12)

#define MICROPY_HW_UART6_TX         (pin_G9)
#define MICROPY_HW_UART6_RX         (pin_G14)

#if 0
// micropython prompt on BMP UART
#define MICROPY_HW_UART_REPL        PYB_UART_6
#define MICROPY_HW_UART_REPL_BAUD   115200
#endif

// I2C buses
#define MICROPY_HW_I2C1_SCL         (pin_B8)
#define MICROPY_HW_I2C1_SDA         (pin_B9)

// SPI buses
#define MICROPY_HW_SPI4_NSS         (pin_E4)
#define MICROPY_HW_SPI4_SCK         (pin_E2)
#define MICROPY_HW_SPI4_MISO        (pin_E5)
#define MICROPY_HW_SPI4_MOSI        (pin_E6)

// CAN buses
#define MICROPY_HW_CAN1_TX          (pin_A12)
#define MICROPY_HW_CAN1_RX          (pin_A11)

// USB config
#define MICROPY_HW_USB_FS           (0)
#define MICROPY_HW_USB_HS           (1)
#define MICROPY_HW_USB_HS_IN_FS     (1)
#define MICROPY_HW_USB_MAIN_DEV     (USB_PHY_HS_ID)
#define MICROPY_HW_USB_CDC_NUM      (3)
#define MICROPY_HW_USB_MSC          (0)

// bkpt for debugger if hard fault and pyb.fault_debug(1)
#define MICROPY_HW_BKPT_IF_RESET    (1)

// DAP

#define MODULE_FREEDAP_ENABLED      (1)
// default calibration values for this board
// after compilation, check with dap.calibrate() values are correct
#define DAP_DEFAULT_DELAY_CONSTANT  36000
#define DAP_DEFAULT_FAST_CLOCK      14400000

// Black Magic Probe

#define MODULE_BMP_ENABLED          (1)
#include "boards/mpconfigbmp.h"
#define PLATFORM_HAS_POWER_SWITCH

/******************************************************************************/
// Bootloader configuration

#define MBOOT_USB_AUTODETECT_PORT   (0)

// configure pin to force entry into the boot loader
#define MBOOT_BOOTPIN_PIN           (pyb_pin_MBOOT)
#define MBOOT_BOOTPIN_PULL          (MP_HAL_PIN_PULL_UP)
#define MBOOT_BOOTPIN_ACTIVE        (0)

// definitions below only to allow compilation of bootloader
#define MICROPY_HW_USRSW_PIN        (pyb_pin_USR)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
#define MICROPY_HW_USRSW_PRESSED    (0)
#define MICROPY_HW_LED_INVERTED     (1) // LEDs are on when pin is driven low
#define MICROPY_HW_LED1             (pyb_pin_LED_RED)
#define MICROPY_HW_LED2             (pyb_pin_LED_GREEN)
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// not truncated
