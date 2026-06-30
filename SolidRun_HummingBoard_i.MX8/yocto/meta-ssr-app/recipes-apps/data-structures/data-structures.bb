SUMMARY = "Data Structures Visualizer"
DESCRIPTION = "Qt6 application for visualizing data structures"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "qt6 qtbase qtdeclarative"

SRCREV = "${AUTOREV}"
SRC_URI = "git://${TOPDIR}/../applications/data-structures;protocol=file"
S = "${WORKDIR}/git"

inherit cmake_qt6 pkgconfig

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/data-structures ${D}${bindir}/data-structures
}
