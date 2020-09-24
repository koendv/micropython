# like boards/manifest.py, but replace boards/inisetup.py with custom ESP32_WROVER/modules/inisetup.py
# ESP32_WROVER/modules/inisetup.py creates main.py
#
freeze("modules", "inisetup.py")
include("$(MPY_DIR)/../extmod/blackmagic/modules/esp32/manifest.py")
freeze("$(MPY_DIR)/drivers/display", "ssd1306.py")
#
#freeze("$(PORT_DIR)/modules")
freeze("$(PORT_DIR)/modules", "apa106.py")
freeze("$(PORT_DIR)/modules", "_boot.py")
freeze("$(PORT_DIR)/modules", "flashbdev.py")
freeze("$(PORT_DIR)/modules", "neopixel.py")
freeze("$(MPY_DIR)/tools", ("upip.py", "upip_utarfile.py"))
freeze("$(MPY_DIR)/ports/esp8266/modules", "ntptime.py")
freeze("$(MPY_DIR)/drivers/dht", "dht.py")
freeze("$(MPY_DIR)/drivers/onewire")
include("$(MPY_DIR)/extmod/uasyncio/manifest.py")
include("$(MPY_DIR)/extmod/webrepl/manifest.py")
