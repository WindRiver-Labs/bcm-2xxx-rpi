SUMMARY = "bootloadr configuration"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://config.txt;beginline=1;endline=6;md5=76e434dc9b8c36fee3da5fae2300af3b"

ALLOW_EMPTY_${PN} = "1"
SRC_URI = "file://config.txt \
	   file://cmdline.txt \
"

S = "${WORKDIR}"

inherit deploy

do_deploy () {
	install -d ${DEPLOYDIR}
	cp ${WORKDIR}/config.txt ${DEPLOYDIR}/config.txt
	cp ${WORKDIR}/cmdline.txt ${DEPLOYDIR}/cmdline.txt
}

addtask deploy before do_build after do_install

COMPATIBLE_MACHINE = "^rpi$"
