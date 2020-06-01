SUMMARY = "U-boot boot scripts for Raspberry Pi"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
COMPATIBLE_MACHINE = "^rpi$"

DEPENDS = "u-boot-mkimage-native"

INHIBIT_DEFAULT_DEPS = "1"

SRC_URI = "file://boot.cmd.in"

EXTERNAL_BOOT_CMD_IN ??= ""
do_compile() {
    if [ -n "${EXTERNAL_BOOT_CMD_IN}" -a -f "${EXTERNAL_BOOT_CMD_IN}" ]; then
        sed -e 's/@@KERNEL_IMAGETYPE@@/${KERNEL_IMAGETYPE}/' \
            -e 's/@@KERNEL_BOOTCMD@@/${KERNEL_BOOTCMD}/' \
            "${EXTERNAL_BOOT_CMD_IN}" > "${WORKDIR}/boot.cmd"
    else
        sed -e 's/@@KERNEL_IMAGETYPE@@/${KERNEL_IMAGETYPE}/' \
            -e 's/@@KERNEL_BOOTCMD@@/${KERNEL_BOOTCMD}/' \
            "${WORKDIR}/boot.cmd.in" > "${WORKDIR}/boot.cmd"
    fi
    mkimage -A arm -T script -C none -n "Boot script" -d "${WORKDIR}/boot.cmd" boot.scr
}

inherit deploy nopackages

do_deploy() {
    install -d ${DEPLOYDIR}
    if ${@bb.utils.contains('DISTRO_FEATURES', 'ostree', 'true', 'false', d)}; then
        install -m 0644 boot.scr ${DEPLOYDIR}/boot-rpi.scr
    else
        install -m 0644 boot.scr ${DEPLOYDIR}
    fi
}

addtask do_deploy after do_compile before do_build
