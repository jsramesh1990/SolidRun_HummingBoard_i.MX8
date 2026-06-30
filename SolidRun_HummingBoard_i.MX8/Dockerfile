FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    vim \
    gdb \
    valgrind \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    qml6-module-qtquick \
    qml6-module-qtquick-controls \
    qml6-module-qtquick-layouts \
    libqt6serialport6-dev \
    libqt6mqtt6-dev \
    libsqlite3-dev \
    libmosquitto-dev \
    libgpiod-dev \
    libudev-dev \
    systemd-dev \
    gawk \
    diffstat \
    unzip \
    texinfo \
    chrpath \
    socat \
    cpio \
    python3-pip \
    xz-utils \
    libsdl1.2-dev \
    xterm \
    zstd \
    liblz4-tool \
    file \
    && rm -rf /var/lib/apt/lists/*

# Install Python packages
RUN pip3 install pytest pytest-cov pylint black sphinx numpy pyserial paho-mqtt

# Create workspace
WORKDIR /workspace

# Set environment variables
ENV QT_VERSION=6.4.0
ENV QT_DIR=/opt/Qt/${QT_VERSION}/gcc_64

# Default command
CMD ["/bin/bash"]
