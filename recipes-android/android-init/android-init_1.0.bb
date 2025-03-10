DESCRIPTION = "This installs an android-init service which loads /system/bin/init with the /init.rc file which loads logd and servicemanager"
PR = "r0"
SRC_URI = "file://init.rc \
    file://android-init.service"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"
S = "${WORKDIR}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

do_install() {
    install -m 0644 ${WORKDIR}/init.rc ${D}/init.rc

    install -d ${D}/lib/systemd/system/multi-user.target.wants/
    cp ${WORKDIR}/android-init.service ${D}/lib/systemd/system/
    ln -s ../android-init.service ${D}/lib/systemd/system/multi-user.target.wants/android-init.service
}

FILES:${PN} += "/init.rc /lib/systemd/system/"
