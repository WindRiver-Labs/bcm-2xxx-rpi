#
# Copyright (C) 2017 Wind River Systems, Inc.
#

TARGET_SUPPORTED_KTYPES_bcm-2xxx-rpi = "standard preempt-rt"

KBRANCH_DEFAULT_standard_bcm-2xxx-rpi = "standard/${KMACHINE}"
KBRANCH_DEFAULT_preempt-rt_bcm-2xxx-rpi = "standard/preempt-rt/${KMACHINE}"

KERNEL_DEVICETREE_bcm-2xxx-rpi = "bcm2710-rpi-3-b.dtb"
