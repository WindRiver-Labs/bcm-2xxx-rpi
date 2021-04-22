FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append_bcm-2xxx-rpi4 = " \
	file://0001-config-add-BSP-specific-configuration-in-config.txt.patch \
"

VC4DTBO_bcm-2xxx-rpi4 ?= "vc4-fkms-v3d"


