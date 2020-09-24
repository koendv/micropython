#define MICROPY_HW_BOARD_NAME       "DEVEBOX STM32H7XX"
#define MICROPY_HW_MCU_NAME         "STM32H743"


#define MICROPY_PY_PYB_LEGACY       (0)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SERVO     (0)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SDCARD    (1)
#define MICROPY_HW_ENABLE_MMCARD    (0)


// Settings for 216 MHz cpu clock.
// Values from stm32cubemx clock configuration.
// HSE external crystal is 25 MHz.

#define MICROPY_HW_CLK_PLLM (25)
#define MICROPY_HW_CLK_PLLN (432)
#define MICROPY_HW_CLK_PLLP (2)
#define MICROPY_HW_CLK_PLLQ (9)
#define MICROPY_HW_CLK_PLLR (2)

// Settings for USB clock.
// Values from stm32cubemx clock configuration.
// HSE external crystal is 25 MHz.
#define MICROPY_HW_CLK_PLL3M (5)
#define MICROPY_HW_CLK_PLL3N (48)
#define MICROPY_HW_CLK_PLL3P (5)
#define MICROPY_HW_CLK_PLL3Q (5)
#define MICROPY_HW_CLK_PLL3R (2)

// AXI bus at 108 MHz, 1 wait state.
// From cubemx -> Pinout & Configuration -> System Core -> RCC -> Parameter Settings -> System Parameters -> Flash Latency
// See RM0433 Reference Manual, Table 17 "FLASH recommended number of wait states and programming delay."
#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_1

// RTC
// LSE external crystal is 32768 Hz.
#define MICROPY_HW_RTC_USE_LSE      (1)
#define MICROPY_HW_RTC_USE_US       (0)

// USB config
#define MICROPY_HW_USB_FS (1)
//#define MICROPY_HW_USB_HS           (1)
//#define MICROPY_HW_USB_HS_IN_FS     (1)
//#define MICROPY_HW_USB_MAIN_DEV     (USB_PHY_FS_ID)
#define MICROPY_HW_USB_CDC_NUM      (2)
#define MICROPY_HW_USB_MSC          (0)

// pushbutton
#define MICROPY_HW_USRSW_PIN        (pyb_pin_USRSW1)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_FALLING)
#define MICROPY_HW_USRSW_PRESSED    (0)

// Winbond W25Q64 64Mbit external QSPI flash
#define MICROPY_HW_QSPIFLASH_SIZE_BITS_LOG2 (26)
#define MICROPY_HW_QSPIFLASH_CS     (pyb_pin_QSPI_BK1_NCS)
#define MICROPY_HW_QSPIFLASH_SCK    (pyb_pin_QSPI_CLK)
#define MICROPY_HW_QSPIFLASH_IO0    (pyb_pin_QSPI_BK1_IO0)
#define MICROPY_HW_QSPIFLASH_IO1    (pyb_pin_QSPI_BK1_IO1)
#define MICROPY_HW_QSPIFLASH_IO2    (pyb_pin_QSPI_BK1_IO2)
#define MICROPY_HW_QSPIFLASH_IO3    (pyb_pin_QSPI_BK1_IO3)

// SPI flash, block device config (for use as filesystem)
extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? ((1 << MICROPY_HW_QSPIFLASH_SIZE_BITS_LOG2) / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))
#define MICROPY_HW_BDEV_SPIFLASH_EXTENDED (&spi_bdev) // for extended block protocol
#define MICROPY_HW_FLASH_FS_LABEL   "BMP"

// TFT/OLED display connector
// used to connect target

#define MICROPY_HW_SPI2_SCK                 (pin_B13)
#define MICROPY_HW_SPI2_MISO                (pin_B14)
#define MICROPY_HW_SPI2_MOSI                (pin_B15)
#define MICROPY_HW_SPI2_CS                  (pin_B12)

// DCMI connector for OV2640-200/OV5640-500 camera.

// SD card. Detect switch missing.
#define MICROPY_HW_SDMMC_D0                 (pyb_pin_SD_D0)
#define MICROPY_HW_SDMMC_D1                 (pyb_pin_SD_D1)
#define MICROPY_HW_SDMMC_D2                 (pyb_pin_SD_D2)
#define MICROPY_HW_SDMMC_D3                 (pyb_pin_SD_D3)
#define MICROPY_HW_SDMMC_CK                 (pyb_pin_SD_CK)
#define MICROPY_HW_SDMMC_CMD                (pyb_pin_SD_CMD)
#define MICROPY_HW_SDCARD_DETECT_PIN        (pyb_pin_SD_SW) // XXX dummy, no switch at this pin
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)
#define MICROPY_HW_SDCARD_MOUNT_AT_BOOT     (0)

// UART
#define MICROPY_HW_UART2_TX     (pin_A3)
#define MICROPY_HW_UART2_RX     (pin_A2)

#define MICROPY_HW_UART7_TX     (pin_E8)
#define MICROPY_HW_UART7_RX     (pin_E7)

// I2C
#define MICROPY_HW_I2C1_SCL     (pin_B8)
#define MICROPY_HW_I2C1_SDA     (pin_B9)

#define MICROPY_HW_I2C2_SCL     (pin_B10)
#define MICROPY_HW_I2C2_SDA     (pin_B11)

// SPI
#define MICROPY_HW_SPI1_SCK     (pin_A5)
#define MICROPY_HW_SPI1_MISO    (pin_A6)
#define MICROPY_HW_SPI1_MOSI    (pin_A7)
#define MICROPY_HW_SPI1_CS      (pin_A4)

// CAN
#define MICROPY_HW_CAN1_TX      (pin_B9)
#define MICROPY_HW_CAN1_RX      (pin_B8)

// DAP

#define MODULE_FREEDAP_ENABLED         (1)
// default calibration values for this board
// after compilation, check with dap.calibrate() values are correct
#define DAP_DEFAULT_DELAY_CONSTANT     36000
#define DAP_DEFAULT_FAST_CLOCK         9000000

// Black Magic Probe

// bkpt for debugger if hard fault and pyb.fault_debug(1)
#define MICROPY_HW_BKPT_IF_RESET  (1)

#define MODULE_BMP_ENABLED        (1)

#include "boards/mpconfigbmp.h"

/******************************************************************************/
// Bootloader configuration

//#define MBOOT_USB_AUTODETECT_PORT   (0)
#define MBOOT_FSLOAD                (0)

// configure pin to force entry into the boot loader
#define MBOOT_BOOTPIN_PIN           (pyb_pin_USRSW2)
#define MBOOT_BOOTPIN_PULL          (MP_HAL_PIN_PULL_UP)
#define MBOOT_BOOTPIN_ACTIVE        (0)

// definitions below only to allow compilation of bootloader
#define MICROPY_HW_LED_INVERTED     (1) // LEDs are on when pin is driven low
#define MICROPY_HW_LED1             (pyb_pin_LED)
#define MICROPY_HW_LED2             (pyb_pin_PD9) // pin has no led, but LED2 has to be defined to compile bootloader XXX
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_low(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_high(pin))

// not truncated
