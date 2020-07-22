FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

DEPENDS_append_rpi = " rpi-u-boot-scr bcm2835-bootfiles"

UBOOT_RPI4_SUPPORT_PATCHES = " \
    file://0001-usb-xhci-Add-missing-cache-flush-in-the-scratchpad-a.patch \
    file://0002-usb-xhci-Use-only-32-bit-accesses-in-xhci_writeq-xhc.patch \
    file://0003-pci-Move-some-PCIe-register-offset-definitions-to-a-.patch \
    file://0004-rpi4-shorten-a-mapping-for-the-DRAM.patch \
    file://0005-rpi4-add-a-mapping-for-the-PCIe-XHCI-controller-MMIO.patch \
    file://0006-linux-bitfield.h-Add-primitives-for-manipulating-bit.patch \
    file://0007-pci-Add-some-PCI-Express-capability-register-offset-.patch \
    file://0008-pci-Add-driver-for-Broadcom-BCM2711-SoC-PCIe-control.patch \
    file://0009-configs-Enable-support-for-the-XHCI-controller-on-RP.patch \
    file://0010-arm-rpi-Add-function-to-trigger-VL805-s-firmware-loa.patch \
    file://0011-usb-xhci-Load-Raspberry-Pi-4-VL805-s-firmware.patch \
    file://0001-rpi_4-defconfigs-Add-CONFIG_CMD_BOOT-menu.patch \
    file://0002-rpi.h-Add-ostree-default-variables.patch \
    file://boot_cmd.patch \
    file://pcie-usb-linux-yocto.patch \
    file://0001-fs-fat-fat.c-Do-not-perform-zero-block-reads-if-ther.patch \
    file://0001-qemu-arm64-Defaults-for-booting-with-ostree.patch \
    file://0001-xhci-Add-polling-support-for-USB-keyboards.patch \
    file://0002-usb_kbd-Do-not-fail-the-keyboard-if-it-does-not-have.patch \
    file://0003-common-usb.c-Work-around-keyboard-reporting-USB-devi.patch \
    file://0004-xhci-ring.c-Add-the-poll_pend-state-to-properly-abor.patch \
    file://0005-xhci-ring-Fix-crash-when-issuing-usb-reset.patch \
    file://0006-usb.c-Add-a-retry-in-the-usb_prepare_device.patch \
    file://0002-bcmgenet-Add-support-for-rgmii-rxid.patch \
    file://0001-bcmgenet-fix-DMA-buffer-management.patch \
    file://0001-bcm2835-Add-simiple-framebuffer-for-use-with-fkms.patch \
"

SRC_URI_append_raspberrypi4 = "${UBOOT_RPI4_SUPPORT_PATCHES}"

# Also build a specfic qemu-u-boot.bin

do_configure_append_rpi() {
    rm -rf ${B}-qemu
    mkdir -p ${B}-qemu
    oe_runmake -C ${S} O=${B}-qemu qemu_arm64_config
}

do_compile_append_rpi() {
    echo ${UBOOT_LOCALVERSION} > ${B}-qemu/.scmversion
    oe_runmake -C ${S} O=${B}-qemu ${UBOOT_MAKE_TARGET}
}

do_deploy_append_rpi() {
    ocwd=$PWD
    install -D -m 644 ${B}-qemu/${UBOOT_BINARY} ${DEPLOYDIR}/qemu-${UBOOT_IMAGE}
    cd ${DEPLOYDIR}
    rm -f qemu-${UBOOT_BINARY} qemu-${UBOOT_SYMLINK}
    ln -sf qemu-${UBOOT_IMAGE} qemu-${UBOOT_SYMLINK}
    ln -sf qemu-${UBOOT_IMAGE} qmeu-${UBOOT_BINARY}
    cd $ocwd
}
