# MCU settings
MCU_SERIES = f7
MCU_ARCH = stm32
CMSIS_MCU = STM32F723xx
MICROPY_FLOAT_IMPL = single
AF_FILE = boards/stm32f722_af.csv
LD_FILES = $(BOARD_DIR)/f723.ld boards/common_blifs.ld
TEXT0_ADDR = 0x08010000
TEXT0_SECTIONS = .isr_vector .text .data

# MicroPython settings
MICROPY_PY_BLUETOOTH = 0
MICROPY_BLUETOOTH_NIMBLE = 0
MICROPY_BLUETOOTH_BTSTACK = 0
MICROPY_PY_LWIP = 0
MICROPY_PY_NETWORK_CYW43 = 0
MICROPY_PY_USSL = 0
MICROPY_SSL_MBEDTLS = 0
MICROPY_VFS_LFS2 = 1

FROZEN_MANIFEST = $(BOARD_DIR)/manifest.py

STLINK3MINI = 1

# black magic probe
MODULE_BMP_ENABLED=1
BMP_ADD_MISSING=1
MODULE_FREEDAP_ENABLED=1

#not truncated