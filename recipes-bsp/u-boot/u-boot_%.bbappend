FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

DEPENDS_append_rpi = " rpi-u-boot-scr bcm2835-bootfiles"

UBOOT_RPI4_SUPPORT_PATCHES = " \
    file://0001-rpi_4-defconfigs-Add-CONFIG_CMD_BOOT-menu.patch \
    file://0002-rpi.h-Add-ostree-default-variables.patch \
"

SRC_URI_append_raspberrypi4 = "${UBOOT_RPI4_SUPPORT_PATCHES}"

