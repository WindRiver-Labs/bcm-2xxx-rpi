#@TYPE: Machine inc.
#@NAME: bcm-2xxx-rpi layer

DEFAULTTUNE = "cortexa53"
require conf/machine/include/tune-cortexa53.inc

MACHINE_FEATURES += "usbhost ext3 screen alsa vfat"

KERNEL_IMAGETYPE = "Image"

SERIAL_CONSOLE = "115200 ttyS0"

IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE ?= "bcm-2xxx-rpi-sdimage.wks"
IMAGE_INSTALL_append = " kernel-devicetree kernel-image-image"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"

UBOOT_MACHINE = "rpi_3_defconfig"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE_virtclass-multilib-lib32 ?= "armv7athf-neon"

COMPATIBLE_HOST_pn-netmap_bcm-2xxx-rpi = "null"

PREFERRED_PROVIDER_virtual/xserver = "xserver-xorg"

XSERVER = "xserver-xorg \
           xf86-input-evdev \
           xf86-input-mouse \
           xf86-video-fbdev \
           xf86-input-keyboard"

