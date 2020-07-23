require linux-yocto-bcm-2xxx-rpi.inc

KBRANCH_rpi = "standard/bcm-2xxx-rpi"

FILESEXTRAPATHS_prepend_bcm-2xxx-rpi4 := "${THISDIR}/files:"
SRC_URI_append_bcm-2xxx-rpi4 = " \
    file://tmp-kernel-config-v5.8.cfg \
"
