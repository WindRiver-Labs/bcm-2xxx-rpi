FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_bcm-2xxx-rpi4 = " file://hidden-suspend-button.patch"
