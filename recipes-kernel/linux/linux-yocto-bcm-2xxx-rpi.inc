#
# Copyright (C) 2019 Wind River Systems, Inc.
#

TARGET_SUPPORTED_KTYPES_rpi = "standard"
COMPATIBLE_MACHINE_rpi = "bcm-2xxx-rpi4"

inherit kernel siteinfo
KERNEL_DTC_FLAGS_append_rpi = " -@ -H epapr"

KERNEL_VERSION_SANITY_SKIP = "1"
SRCREV_machine_rpi ?= "${AUTOREV}"
SRCREV_meta_rpi ?= "${AUTOREV}"
