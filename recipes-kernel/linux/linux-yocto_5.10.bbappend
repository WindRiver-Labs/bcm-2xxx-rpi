require linux-yocto-bcm-2xxx-rpi.inc

KBRANCH_rpi = "v5.10/standard/bcm-2xxx-rpi"

LINUX_VERSION_rpi ?= "5.10.x"

FILESEXTRAPATHS_prepend_bcm-2xxx-rpi4 := "${THISDIR}/files:"
SRC_URI_append_bcm-2xxx-rpi4 = " \
    file://0001-driver-drm-vc4-fix-build-issue.patch \
"
