

# MicroPython
=======================
<p align="center">
  <img src="https://raw.githubusercontent.com/micropython/micropython/master/logo/upython-with-micro.jpg" alt="MicroPython Logo"/>
</p>

## Overview
This is a micropython debugger probe. The probe provides

- a gdb server, to debug using gdb 
- a cmsis-dap probe, to debug using openocd and pyocd
- micropython extension modules, to manipulate target memory and registers from micropython scripts.

The sources for the micropython debugger probe are spread over four gits:

- [bmp](http://www.github.com/koendv/bmp): build script, binaries, doc
- [micropython](http://www.github.com/koendv/micropython) micropython, patched. Board definition files.
- [blackmagic](http://www.github.com/koendv/blackmagic) Black Magic Probe, patched into a micropython module
- [free-dap](http://www.github.com/koendv/free-dap) free-dap, patched into a micropython module.

These are the micropython source files.

## Specifics

This version of micropython has patches applied to:

- periodically call Black Magic Probe and free-dap from the micropython event loop: ``bmp_loop()`` and ``dap_loop()`` in ``mphalport.c``.
- tell micropython garbage collection not to free memory allocated by Black Magic Probe: ``MICROPY_PORT_ROOT_POINTER_BMP``
- code to flush an usb stream, else a 64-byte usb vcp packet never gets transmitted. ``pyb_usb_vcp_ioctl()``
- enough support for STM32H750 processors to get micropython to compile ``STM32H750xx``.
- support for crc calculations in hardware ( ``hal_crc.c`` and ``hal_crc_ex.c`` in  ``ports/stm32/Makefile``. Used to calculate checksums for the gdb ``compare-sections`` command.
- set usb interface descriptors from ``mpconfigboard.h``: ``USBD_INTERFACE_CDC0_STRING``, ``USBD_INTERFACE_CDC1_STRING``, ``USBD_INTERFACE_CDC2_STRING``.
- expose the micropython usb hid device to C extension modules (``usbd_hid_interface()`` in ``usb.c``). Needed to implement the dap probe, a usb hid device.
- format the micropython internal file system, and install fresh ``boot.py``  and ``main.py`` files: ``machine.factory_reset()``
- implement a soft breakpoint in the micropython reset handler, so you can use a debugger probe to debug micropython if micropython unexpectedly resets: ``MICROPY_HW_BKPT_IF_RESET``
- board definition files for various boards (``STLINK3MINI``, ``DEVEBOX_STM32H743``, ``DEVEBOX_STM32H750``)

