SUMMARY = "bootloadr configuration"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://config.txt;beginline=1;endline=6;md5=76e434dc9b8c36fee3da5fae2300af3b"

SRC_URI = "file://config.txt \
	   file://cmdline.txt \
	   file://cmdline-ostree.txt \
"

S = "${WORKDIR}"

inherit deploy

PACKAGES = "${PN}"
FILES_${PN} = "/boot/*"

do_install () {
	install -d ${D}/boot
	cp ${WORKDIR}/config.txt ${D}/boot/config.txt
	if ${@bb.utils.contains('DISTRO_FEATURES', 'ostree', 'true', 'false', d)}; then
		cp ${WORKDIR}/cmdline-ostree.txt ${D}/boot/cmdline.txt
	else
		cp ${WORKDIR}/cmdline.txt ${D}/boot/cmdline.txt
	fi
}

do_deploy() {
    install -d ${DEPLOYDIR}/
    cp -rf ${D}/boot/*.txt ${DEPLOYDIR}/
}

addtask deploy before do_build after do_install

COMPATIBLE_MACHINE = "^rpi$"
