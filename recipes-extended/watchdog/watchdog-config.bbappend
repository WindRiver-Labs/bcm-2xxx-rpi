# The Raspberry Pi4 needs a 15 second watch dog

do_install_append_rpi() {
	echo "watchdog-timeout = 15" >> ${D}/etc/watchdog.conf
}


