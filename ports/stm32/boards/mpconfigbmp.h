// Black Magic Probe

#if MODULE_BMP_ENABLED

void bmp_loop(void);
#define	MICROPY_VM_HOOK_INIT        bmp_loop();
#define	MICROPY_VM_HOOK_LOOP        bmp_loop();
#define	MICROPY_VM_HOOK_RETURN      bmp_loop();

#define USBD_MANUFACTURER_STRING      "Black Sphere Technologies"
#if MODULE_FREEDAP_ENABLED == 1
// cmsis tools look for 'CMSIS-DAP' in the product description
#define USBD_PRODUCT_HS_STRING        "Black Magic Probe CMSIS-DAP HS"
#define USBD_PRODUCT_FS_STRING        "Black Magic Probe CMSIS-DAP FS"
#else
#define USBD_PRODUCT_HS_STRING        "Black Magic Probe HS"
#define USBD_PRODUCT_FS_STRING        "Black Magic Probe FS"
#endif
#define USBD_CONFIGURATION_HS_STRING  "Black Magic Probe HS Config"
#define USBD_INTERFACE_HS_STRING      "Black Magic Probe HS Interface"
#define USBD_CONFIGURATION_FS_STRING  "Black Magic Probe FS Config"
#define USBD_INTERFACE_FS_STRING      "Black Magic Probe FS Interface"

// usb interface descriptors
// linux udev looks for "Black Magic GDB Server" and "Black Magic UART Port"
// see /etc/udev/rules.d/99-blackmagic.rules
#define USBD_INTERFACE_CDC0_STRING    "Micropython"
#define USBD_INTERFACE_CDC1_STRING    "Black Magic GDB Server"
#define USBD_INTERFACE_CDC2_STRING    "Black Magic UART Port"

// tune usb buffer size
#define USBD_CDC_RX_DATA_SIZE (2048) // must be 2 or greater, and a power of 2
#define USBD_CDC_TX_DATA_SIZE (4096) // can be any value (was 2048)

#endif
