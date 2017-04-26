#@TYPE: Machine inc.
#@NAME: bcm-2xxx-rpi layer

DEFAULTTUNE = "cortexa7thf-neon"
require conf/machine/include/tune-cortexa7.inc

MACHINE_FEATURES += "usbhost ext3 screen alsa vfat"

KERNEL_IMAGETYPE = "zImage"

SERIAL_CONSOLE = "115200 ttyS0"

IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE = "sdimage.wks"
IMAGE_INSTALL_append = " kernel-devicetree kernel-image-zimage"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"

PREFERRED_PROVIDER_virtual/xserver = "xserver-xorg"

XSERVER = "xserver-xorg \
           xf86-input-evdev \
           xf86-input-mouse \
           xf86-video-fbdev \
           xf86-input-keyboard"
