#@TYPE: Machine inc.
#@NAME: bcm-2xxx-rpi layer

DEFAULTTUNE = "cortexa72"
require conf/machine/include/tune-cortexa72.inc

require conf/machine/include/soc-family.inc
SOC_FAMILY =. "rpi:"

MACHINE_FEATURES += "usbhost ext3 screen alsa vfat"

KERNEL_IMAGETYPE = ""
KERNEL_IMAGETYPES = "Image.gz Image"

SERIAL_CONSOLE = "115200 ttyS0"

# wic
WIC_CREATE_EXTRA_ARGS = "--no-fstab-update"
IMAGE_FSTYPES += "tar.bz2 wic wic.bmap ext4"
WKS_FILE ?= "bcm-2xxx-rpi-sdimage.wks"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"
do_image_wic[depends] += "u-boot:do_deploy"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE_virtclass-multilib-lib32 ?= "armv7athf-neon"

PREFERRED_PROVIDER_virtual/kernel ??= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.4%"

RPI_KERNEL_DEVICETREE_OVERLAYS ?= " \
    overlays/at86rf233.dtbo \
    overlays/disable-bt.dtbo \
    overlays/dwc2.dtbo \
    overlays/gpio-key.dtbo \
    overlays/hifiberry-amp.dtbo \
    overlays/hifiberry-dac.dtbo \
    overlays/hifiberry-dacplus.dtbo \
    overlays/hifiberry-digi.dtbo \
    overlays/i2c-rtc.dtbo \
    overlays/iqaudio-dac.dtbo \
    overlays/iqaudio-dacplus.dtbo \
    overlays/miniuart-bt.dtbo \
    overlays/mcp2515-can0.dtbo \
    overlays/pitft22.dtbo \
    overlays/pitft28-resistive.dtbo \
    overlays/pitft28-capacitive.dtbo \
    overlays/pitft35-resistive.dtbo \
    overlays/pps-gpio.dtbo \
    overlays/rpi-ft5406.dtbo \
    overlays/rpi-poe.dtbo \
    overlays/vc4-kms-v3d.dtbo \
    overlays/vc4-fkms-v3d.dtbo \
    overlays/w1-gpio-pullup.dtbo \
    overlays/w1-gpio.dtbo \
    overlays/gpio-ir.dtbo \
    overlays/gpio-ir-tx.dtbo \
"

def make_dtb_boot_files(d):
    # Generate IMAGE_BOOT_FILES entries for device tree files listed in
    # KERNEL_DEVICETREE.
    alldtbs = d.getVar('KERNEL_DEVICETREE')
    imgtyp = d.getVar('KERNEL_IMAGETYPE')

    def transform(dtb):
        base = os.path.basename(dtb)
        if dtb.endswith('dtb'):
            # eg: whatever/bcm2708-rpi-b.dtb has:
            #     DEPLOYDIR file: bcm2708-rpi-b.dtb
            #     destination: bcm2708-rpi-b.dtb
            return base
        elif dtb.endswith('dtbo'):
            # overlay dtb:
            # eg: overlays/hifiberry-amp.dtbo has:
            #     DEPLOYDIR file: hifiberry-amp.dtbo
            #     destination: overlays/hifiberry-amp.dtbo
            return '{};{}'.format(base, dtb)

    return ' '.join([transform(dtb) for dtb in alldtbs.split(' ') if dtb])



# For runqemu, these settings are from qemuarm64
IMAGE_CLASSES += "qemuboot"

EXTRA_IMAGEDEPENDS += "qemu-native qemu-helper-native"

QB_SYSTEM_NAME = "qemu-system-aarch64"
QB_MACHINE = "-machine virt"
QB_CPU = "-cpu cortex-a57"
QB_CPU_KVM = "-cpu host -machine gic-version=3"
QB_DRIVE_TYPE = "/dev/vdb"
# Standard Serial console
QB_KERNEL_CMDLINE_APPEND = "console=ttyAMA0"
QB_DEFAULT_KERNEL = "Image"
# For graphics to work we need to define the VGA device as well as the necessary USB devices
QB_OPT_APPEND = "-show-cursor -device virtio-gpu-pci"
QB_OPT_APPEND += "-device qemu-xhci -device usb-tablet -device usb-kbd"
# Add the 'virtio-rng-pci' device otherwise the guest may run out of entropy
QB_OPT_APPEND += "-object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-pci,rng=rng0"
# Virtio Networking support
QB_TAP_OPT = "-netdev tap,id=net0,ifname=@TAP@,script=no,downscript=no"
QB_NETWORK_DEVICE = "-device virtio-net-device,netdev=net0,mac=@MAC@"
# Virtio block device
QB_ROOTFS_OPT = "-drive id=disk0,file=@ROOTFS@,if=none,format=raw -device virtio-blk-device,drive=disk0"
# Virtio serial console
QB_SERIAL_OPT = "-device virtio-serial-device -chardev null,id=virtcon -device virtconsole,chardev=virtcon"
QB_TCPSERIAL_OPT = "-device virtio-serial-device -chardev socket,id=virtcon,port=@PORT@,host=127.0.0.1 -device virtconsole,chardev=virtcon"
