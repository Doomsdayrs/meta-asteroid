SUMMARY = "Nemomobile's sensorfw"
HOMEPAGE = "https://github.com/sailfishos/sensorfw"
LICENSE = "LGPL-2.1-or-later"
LIC_FILES_CHKSUM = "file://COPYING;md5=2d5025d4aa3495befef8f17206a5b0a1"

SRC_URI = "git://github.com/sailfishos/sensorfw.git;protocol=https;branch=master \
           file://0001-Do-not-hide-stepcounter-by-default.patch \
           file://0002-Add-heart-rate-monitor-sensor-with-hybris-adaptor.patch \
           file://0003-Add-Wrist-gesture-sensor-via-libhybris-adaptor.patch \
           file://0004-Fix-compilation-when-autohybris-is-used.patch \
           file://0005-Fix-compilation-when-hybris-is-used.patch \
           file://sensorfwd.service"
SRCREV = "0.12.6"
PR = "r1"
PV = "+git${SRCPV}"
S = "${WORKDIR}/git"

# Avoid potential renaming of the ipk.
DEBIANNAME:${PN} = "${PN}"
DEBIANNAME:${PN}-src = "${PN}-src"
DEBIANNAME:${PN}-dbg = "${PN}-dbg"
DEBIANNAME:${PN}-dev = "${PN}-dev"

inherit qmake5 pkgconfig

do_configure:prepend() {
    sed "s=@LIB@=lib/=g" ../git/sensord-qt5.pc.in > ../git/sensord-qt5.pc
    sed -i 's/$$\[QT_INSTALL_LIBS\]/\/usr\/lib/g' ../git/core/core.pro
    sed -i '/include( doc\/doc.pri )/d' ../git/sensorfw.pro
    sed -i 's:-L/usr/lib ::' ../git/core/hybris.pro
}

do_install:append() {
    install -d ${D}/etc/sensorfw/ ${D}/lib/systemd/system/multi-user.target.wants/
    cp ${S}/config/sensord-hybris.conf ${D}/etc/sensorfw/primaryuse.conf
    cp ../sensorfwd.service ${D}/lib/systemd/system/sensorfwd.service
    ln -s ../sensorfwd.service ${D}/lib/systemd/system/multi-user.target.wants/
}

DEPENDS += "qtbase"
