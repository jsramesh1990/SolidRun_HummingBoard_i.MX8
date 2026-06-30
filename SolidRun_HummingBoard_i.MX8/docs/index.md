markdown

# Embedded Learning Platform Documentation

## Overview
The Embedded Learning Platform is a comprehensive system for learning embedded Linux development using the SolidRun HummingBoard i.MX8.

## Architecture
- **Hardware**: SolidRun HummingBoard i.MX8
- **OS**: Yocto-based Linux
- **UI**: Qt6/QML
- **Communication**: MQTT, D-Bus, WebSocket
- **Database**: SQLite

## Development Guide

### Setting Up Development Environment
1. Clone the repository
2. Run `./scripts/setup.sh`
3. Build the project with `./scripts/build.sh`

### Application Structure
- `applications/dashboard/` - Main HMI
- `applications/calculator/` - Scientific calculator
- `applications/data-structures/` - Data structure visualizations
- `applications/embedded/` - Hardware interface examples

### Adding New Features
1. Create a new application in `applications/`
2. Add a Qt6/QML interface
3. Integrate with Yocto layer
4. Add unit tests
5. Update documentation

## Hardware Interfaces

### GPIO
```cpp
// Example GPIO usage
int gpio_pin = 26; // GPIO1_IO0
gpio_set_value(gpio_pin, 1);

I2C
cpp

// Example I2C usage
int fd = i2c_open(1);  // I2C bus 1
i2c_write(fd, 0x48, data, len);

SPI
cpp

// Example SPI usage
int fd = spi_open(0, 0);  // SPI bus 0, CS 0
spi_transfer(fd, tx_buffer, rx_buffer, len);

UART
cpp

// Example UART usage
int fd = uart_open("/dev/ttyS0", 115200);
uart_write(fd, data, len);

CAN
cpp

// Example CAN usage
int fd = can_open("can0");
can_send(fd, id, data, len);

MQTT Communication
Publishing
cpp

mqtt_publish("topic/device", "Hello World");

Subscribing
cpp

mqtt_subscribe("topic/device");

Database
SQLite Operations
cpp

sqlite_exec("CREATE TABLE logs (id INTEGER PRIMARY KEY, message TEXT)");
sqlite_insert("INSERT INTO logs (message) VALUES ('Test')");

System Services

    dashboard.service - Main UI

    gpio.service - GPIO control

    i2c.service - I2C monitoring

    mqtt.service - MQTT broker

    sensors.service - Sensor monitoring

    logger.service - System logging

Testing
bash

# Run unit tests
cd tests/unit
make && ./unit_tests

# Run integration tests
cd tests/integration
pytest -v

# Run hardware tests
cd tests/hardware
./run_tests.sh

Deployment
bash

# Build Yocto image
cd yocto
source sources/poky/oe-init-build-env build
bitbake embedded-learning-image

# Flash to SD card
dd if=build/tmp/deploy/images/hummingboard/embedded-learning-image-hummingboard.wic of=/dev/sdX bs=4M
