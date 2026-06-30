SUMMARY = "GPIO Control Application"
DESCRIPTION = "GPIO control and monitoring application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "libgpiod"

SRCREV = "${AUTOREV}"
SRC_URI = "git://${TOPDIR}/../applications/embedded/gpio;protocol=file"
S = "${WORKDIR}/git"

inherit cmake pkgconfig

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/gpio ${D}${bindir}/gpio
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/../systemd/gpio.service ${D}${systemd_system_unitdir}
}

inherit systemd
SYSTEMD_SERVICE_${PN} = "gpio.service"
