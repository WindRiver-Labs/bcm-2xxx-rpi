CMDLINE_bcm-2xxx-rpi4 = "${@bb.utils.contains("DISTRO_FEATURES", "ostree", "dwc_otg.lpm_enable=0 rootwait", \
			"dwc_otg.lpm_enable=0 console=serial0,115200 root=/dev/mmcblk0p2 rootfstype=ext4 rootwait ip=dhcp", d)}"

PACKAGE_ARCH_bcm-2xxx-rpi4 = "${MACHINE_ARCH}"
