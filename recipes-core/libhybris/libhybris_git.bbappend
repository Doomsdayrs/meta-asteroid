FILESEXTRAPATHS:prepend := "${THISDIR}/libhybris:"
SRCREV = "fae0a52632893cbf3bb7ce0762147b7067db176b"

DEPENDS:append = " wayland "
EXTRA_OECONF:append = " --enable-wayland --with-default-egl-platform=wayland --with-default-hybris-ld-library-path=/usr/libexec/hal-droid/system/lib:/vendor/lib:/system/lib"

COMPATIBLE_MACHINE=""

do_configure:prepend() {
    sed -i "s@=\`\$PKG_CONFIG@=\$\{PKG_CONFIG_SYSROOT_DIR\}\`\$PKG_CONFIG@" ${S}/configure.ac
}
