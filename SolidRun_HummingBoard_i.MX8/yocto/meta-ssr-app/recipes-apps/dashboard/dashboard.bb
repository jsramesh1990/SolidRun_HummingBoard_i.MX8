SUMMARY = "Embedded Learning Platform Dashboard"
DESCRIPTION = "Qt6 dashboard application for HummingBoard"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "qt6 qtbase qtdeclarative qtquickcontrols2 qtserialport qtmqtt qtsql"

SRCREV = "${AUTOREV}"
SRC_URI = "git://${TOPDIR}/../applications/dashboard;protocol=file"
S = "${WORKDIR}/git"

inherit cmake_qt6 pkgconfig

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/dashboard ${D}${bindir}/dashboard
}
