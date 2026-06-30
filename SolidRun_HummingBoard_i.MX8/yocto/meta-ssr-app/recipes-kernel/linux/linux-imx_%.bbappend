FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://0001-custom-gpio.patch \
    file://0002-custom-i2c.patch \
    file://custom_defconfig \
"

# Kernel configuration
KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/custom_defconfig"

# Enable additional drivers
do_configure:append() {
    # Enable GPIO, I2C, SPI, CAN drivers
    echo "CONFIG_GPIO_SYSFS=y" >> ${B}/.config
    echo "CONFIG_I2C_CHARDEV=y" >> ${B}/.config
    echo "CONFIG_SPI_SPIDEV=y" >> ${B}/.config
    echo "CONFIG_CAN=y" >> ${B}/.config
    echo "CONFIG_CAN_VCAN=y" >> ${B}/.config
    echo "CONFIG_CAN_ISOTP=y" >> ${B}/.config
}
