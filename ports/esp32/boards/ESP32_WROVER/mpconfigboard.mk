#FLASH_FREQ = 80m

SDKCONFIG += boards/sdkconfig.base
SDKCONFIG += boards/sdkconfig.240mhz
SDKCONFIG += boards/sdkconfig.spiram

FROZEN_MANIFEST ?= $(BOARD_DIR)/manifest.py

# increase firmware partition size
PART_SRC = $(BOARD_DIR)/partitions.csv

# black magic probe
MCU_SERIES=esp32-wrover
MCU_ARCH=esp32
MODULE_BMP_ENABLED = 1
MODULE_FREEDAP_ENABLED=1
