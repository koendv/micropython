import uos
from flashbdev import bdev


def check_bootsec():
    buf = bytearray(bdev.ioctl(5, 0))  # 5 is SEC_SIZE
    bdev.readblocks(0, buf)
    empty = True
    for b in buf:
        if b != 0xFF:
            empty = False
            break
    if empty:
        return True
    fs_corrupted()


def fs_corrupted():
    import time

    while 1:
        print(
            """\
FAT filesystem appears to be corrupted. If you had important data there, you
may want to make a flash snapshot to try to recover it. Otherwise, perform
factory reprogramming of MicroPython firmware (completely erase flash, followed
by firmware programming).
"""
        )
        time.sleep(3)


def setup():
    check_bootsec()
    print("Performing initial setup")
    uos.VfsLfs2.mkfs(bdev)
    vfs = uos.VfsLfs2(bdev)
    uos.mount(vfs, "/")
    fresh_files()
    return vfs

def fresh_files():
    with open("boot.py", "w") as f:
        f.write(
            """\
# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
#import webrepl
#webrepl.start()
"""
        )
    with open("main.py", "w") as f:
        f.write(
            """\
# This file is executed after boot.py
from pye_mp import pye

import network
def wifi_on():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting...')
        wlan.connect('essid', 'passwd')
        while not wlan.isconnected():
            pass
    print(wlan.ifconfig())

import machine, uos
def sdcard_on():
    machine.Pin(2).init(-1, machine.Pin.PULL_UP)
    uos.mount(machine.SDCard(width=4), "/sd")

def vbat():
    adc=machine.ADC(machine.Pin(34))
    vbat=adc.read()
    vbat*=3.7*2
    vbat/=4095
    return vbat

# for bmp semihosting
import bmp, target, semihosting
semihosting.init()

# for gdb mon python
def repl_callback(s):
  return str(eval(s))
bmp.repl_fun(repl_callback)

#wifi_on()
# Choose one:
# bmp listening on tcp port 3333
#bmp.init(tcp=3333)
# bmp listening on uart1, 115200 baud, pins 22 and 23
#bmp.init(stream=machine.UART(1,115200,rx=22,tx=23))
"""
        )

