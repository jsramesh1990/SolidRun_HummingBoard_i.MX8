SUMMARY = "Embedded Learning Platform Image"
DESCRIPTION = "Complete image for Embedded Learning Platform"

inherit core-image

# Add features
IMAGE_FEATURES += "ssh-server-openssh package-management"

# Add packages
IMAGE_INSTALL += " \
    packagegroup-core-boot \
    packagegroup-core-full-cmdline \
    \
    dashboard \
    calculator \
    data-structures \
    gpio \
    i2c \
    spi \
    uart \
    can \
    mqtt \
    sensors \
    camera \
    \
    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd-analyze', '', d)} \
"

# Root filesystem size
IMAGE_ROOTFS_SIZE = "8192"

# Compress image
IMAGE_FSTYPES += "wic wic.bz2"

# Kernel modules
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-modules"

# Add extra tools
IMAGE_INSTALL += " \
    i2c-tools \
    spi-tools \
    can-utils \
    usbutils \
    gpio-tools \
    mosquitto \
    sqlite3 \
    curl \
    vim \
    git \
"

# Qt6 packages
IMAGE_INSTALL += " \
    qt6-declarative \
    qt6-quickcontrols2 \
    qt6-serialport \
    qt6-mqtt \
    qt6-sql \
"
