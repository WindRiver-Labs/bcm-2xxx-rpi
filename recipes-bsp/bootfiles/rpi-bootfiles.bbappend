do_deploy_append_bcm-2xxx-rpi4() {
    # Add LICENSE file with disclaimer
    (cd ${S} ; ls -C -w 80 *.bin *.dat *.elf) > ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/LICENSE.broadcom
    cat<<EOF>> ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/LICENSE.broadcom

========================================================================
The following applies to the files found in this directory listed above.
========================================================================

EOF
    cat ${S}/LICENCE.broadcom >> ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/LICENSE.broadcom
}
