#include "DeviceManager.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <fcntl.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
{
    enumerateDevices();
}

void DeviceManager::enumerateDevices()
{
    m_devices.clear();
    
    // Scan for GPIO devices
    QDir gpioDir("/sys/class/gpio");
    if (gpioDir.exists()) {
        for (const QString &entry : gpioDir.entryList(QDir::Dirs)) {
            if (entry.startsWith("gpio")) {
                DeviceInfo info;
                info.name = entry;
                info.path = gpioDir.absolutePath() + "/" + entry;
                info.type = "GPIO";
                info.available = true;
                m_devices.append(info);
            }
        }
    }
    
    // Scan for I2C devices
    QDir i2cDir("/dev");
    for (const QString &entry : i2cDir.entryList(QDir::Files)) {
        if (entry.startsWith("i2c-")) {
            DeviceInfo info;
            info.name = entry;
            info.path = "/dev/" + entry;
            info.type = "I2C";
            info.available = true;
            m_devices.append(info);
        }
    }
    
    // Scan for SPI devices
    for (const QString &entry : i2cDir.entryList(QDir::Files)) {
        if (entry.startsWith("spidev")) {
            DeviceInfo info;
            info.name = entry;
            info.path = "/dev/" + entry;
            info.type = "SPI";
            info.available = true;
            m_devices.append(info);
        }
    }
    
    // Scan for UART devices
    for (const QString &entry : i2cDir.entryList(QDir::Files)) {
        if (entry.startsWith("ttyS") || entry.startsWith("ttyUSB")) {
            DeviceInfo info;
            info.name = entry;
            info.path = "/dev/" + entry;
            info.type = "UART";
            info.available = true;
            m_devices.append(info);
        }
    }
    
    emit devicesChanged();
}

bool DeviceManager::scanDevices()
{
    enumerateDevices();
    return true;
}

bool DeviceManager::openDevice(const QString &path)
{
    qDebug() << "Opening device:" << path;
    
    int fd = open(path.toStdString().c_str(), O_RDWR);
    if (fd < 0) {
        emit errorOccurred(path, "Failed to open device");
        return false;
    }
    
    m_deviceHandles[path] = reinterpret_cast<void*>(fd);
    emit deviceOpened(path);
    return true;
}

bool DeviceManager::closeDevice(const QString &path)
{
    if (!m_deviceHandles.contains(path)) {
        return false;
    }
    
    int fd = reinterpret_cast<int>(m_deviceHandles[path]);
    close(fd);
    m_deviceHandles.remove(path);
    emit deviceClosed(path);
    return true;
}

bool DeviceManager::readDevice(const QString &path, QByteArray &data)
{
    if (!m_deviceHandles.contains(path)) {
        return false;
    }
    
    int fd = reinterpret_cast<int>(m_deviceHandles[path]);
    char buffer[256];
    ssize_t bytes = read(fd, buffer, sizeof(buffer));
    
    if (bytes < 0) {
        return false;
    }
    
    data = QByteArray(buffer, bytes);
    emit dataReceived(path, data);
    return true;
}

bool DeviceManager::writeDevice(const QString &path, const QByteArray &data)
{
    if (!m_deviceHandles.contains(path)) {
        return false;
    }
    
    int fd = reinterpret_cast<int>(m_deviceHandles[path]);
    ssize_t bytes = write(fd, data.data(), data.size());
    
    return bytes == data.size();
}
