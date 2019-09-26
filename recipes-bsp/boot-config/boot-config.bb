SUMMARY = "bootloadr configuration"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://config.txt;beginline=1;endline=6;md5=76e434dc9b8c36fee3da5fae2300af3b"

ALLOW_EMPTY_${PN} = "1"
FILESEXTRAPATHS_prepend := "${THISDIR}/:"
SRC_URI = "file://boot-config/config.txt \
	   file://boot-config/cmdline.txt \
"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

do_populate_lic[depends] = "${PN}:do_configure"
do_configure_prepend() {
	cp ${WORKDIR}/boot-config/config.txt ${B}/
}

do_deploy () {
	install -d ${DEPLOYDIR}
	cp ${WORKDIR}/boot-config/config.txt ${DEPLOYDIR}/config.txt
	cp ${WORKDIR}/boot-config/cmdline.txt ${DEPLOYDIR}/cmdline.txt
}

addtask deploy before do_build after do_compile
