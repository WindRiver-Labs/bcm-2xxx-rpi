#
# Copyright (C) 2019 Wind River Systems, Inc.
#

TARGET_SUPPORTED_KTYPES_rpi = "standard"
COMPATIBLE_MACHINE_rpi = "bcm-2xxx-rpi4"

inherit kernel siteinfo
KERNEL_EXTRA_ARGS_append_rpi = " DTC_FLAGS='-@ -H epapr'"
do_compile_append_rpi() {
    if [ "${SITEINFO_BITS}" = "64" ]; then
        cc_extra=$(get_cc_option)
        oe_runmake dtbs CC="${KERNEL_CC} $cc_extra " LD="${KERNEL_LD}" ${KERNEL_EXTRA_ARGS}
    fi
}

SRCREV_machine_rpi ?= "${AUTOREV}"
SRCREV_meta_rpi ?= "${AUTOREV}"
