FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_bcm-2xxx-rpi4 = " \
	file://0001-brcm-Fix-Raspberry-Pi-4B-NVRAM-file.patch \
"
