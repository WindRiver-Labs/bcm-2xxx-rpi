require linux-yocto-bcm-2xxx-rpi.inc

KBRANCH_rpi = "v5.4/standard/bcm-2xxx-rpi"

LINUX_VERSION_rpi ?= "5.4.x"

FILESEXTRAPATHS_prepend_bcm-2xxx-rpi4 := "${THISDIR}/files:"
SRC_URI_append_bcm-2xxx-rpi4 = " \
    file://tmp-kernel-config-v5.4.cfg \
    file://0001-driver-net-lan78xx-fix-building-issue-introduced-by-.patch \
"
