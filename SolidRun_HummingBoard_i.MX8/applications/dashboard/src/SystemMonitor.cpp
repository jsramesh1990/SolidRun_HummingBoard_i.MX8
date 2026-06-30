#include "SystemMonitor.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QNetworkInterface>

SystemMonitor::SystemMonitor(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_monitoring(false)
{
    connect(m_timer, &QTimer::timeout, this, &SystemMonitor::updateStats);
    m_timer->setInterval(1000); // Update every second
    
    // Initial update
    updateStats();
}

SystemMonitor::~SystemMonitor()
{
    if (m_timer) {
        m_timer->stop();
    }
}

void SystemMonitor::setMonitoring(bool enabled)
{
    if (m_monitoring != enabled) {
        m_monitoring = enabled;
        if (enabled) {
            m_timer->start();
        } else {
            m_timer->stop();
        }
        emit monitoringChanged();
    }
}

void SystemMonitor::refresh()
{
    updateStats();
}

void SystemMonitor::updateStats()
{
    m_stats.cpuUsage = getCpuUsage();
    m_stats.memoryUsage = getMemoryUsage();
    m_stats.diskUsage = getDiskUsage();
    m_stats.temperature = getTemperature();
    m_stats.kernelVersion = getKernelVersion();
    m_stats.ipAddress = getIpAddress();
    m_stats.uptime = getUptime();
    
    emit statsChanged();
    
    // Check for alerts
    if (m_stats.temperature > 85.0) {
        emit alert(QString("High temperature: %1°C").arg(m_stats.temperature));
    }
}

double SystemMonitor::getCpuUsage()
{
    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0.0;
    }
    
    QTextStream in(&file);
    QString line = in.readLine();
    file.close();
    
    if (!line.startsWith("cpu ")) {
        return 0.0;
    }
    
    QStringList parts = line.split(" ", Qt::SkipEmptyParts);
    if (parts.size() < 5) {
        return 0.0;
    }
    
    // Static variables for previous values
    static unsigned long prevIdle = 0;
    static unsigned long prevTotal = 0;
    
    unsigned long user = parts[1].toULong();
    unsigned long nice = parts[2].toULong();
    unsigned long system = parts[3].toULong();
    unsigned long idle = parts[4].toULong();
    
    unsigned long total = user + nice + system + idle;
    
    double usage = 0.0;
    if (prevTotal > 0) {
        unsigned long diffTotal = total - prevTotal;
        unsigned long diffIdle = idle - prevIdle;
        usage = 100.0 * (diffTotal - diffIdle) / diffTotal;
    }
    
    prevIdle = idle;
    prevTotal = total;
    
    return usage;
}

double SystemMonitor::getMemoryUsage()
{
    QFile file("/proc/meminfo");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0.0;
    }
    
    QTextStream in(&file);
    unsigned long total = 0;
    unsigned long available = 0;
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("MemTotal:")) {
            total = line.split(" ", Qt::SkipEmptyParts)[1].toULong();
        } else if (line.startsWith("MemAvailable:")) {
            available = line.split(" ", Qt::SkipEmptyParts)[1].toULong();
        }
    }
    file.close();
    
    if (total == 0) {
        return 0.0;
    }
    
    return 100.0 * (total - available) / total;
}

double SystemMonitor::getDiskUsage()
{
    QProcess process;
    process.start("df", QStringList() << "/");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    if (lines.size() < 2) {
        return 0.0;
    }
    
    QStringList parts = lines[1].split(" ", Qt::SkipEmptyParts);
    if (parts.size() < 5) {
        return 0.0;
    }
    
    unsigned long used = parts[2].toULong();
    unsigned long total = parts[1].toULong();
    
    if (total == 0) {
        return 0.0;
    }
    
    return 100.0 * used / total;
}

double SystemMonitor::getTemperature()
{
    QFile file("/sys/class/thermal/thermal_zone0/temp");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0.0;
    }
    
    QTextStream in(&file);
    QString temp = in.readLine();
    file.close();
    
    return temp.toDouble() / 1000.0;
}

QString SystemMonitor::getKernelVersion()
{
    QFile file("/proc/version");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "Unknown";
    }
    
    QTextStream in(&file);
    QString version = in.readLine();
    file.close();
    
    // Extract just the version number
    QStringList parts = version.split(" ");
    if (parts.size() >= 3) {
        return parts[2];
    }
    
    return version;
}

QString SystemMonitor::getIpAddress()
{
    for (const QNetworkInterface &interface : QNetworkInterface::allInterfaces()) {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
            !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    return entry.ip().toString();
                }
            }
        }
    }
    return "No network";
}

int SystemMonitor::getUptime()
{
    QFile file("/proc/uptime");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }
    
    QTextStream in(&file);
    QString uptime = in.readLine();
    file.close();
    
    return uptime.split(" ")[0].toInt();
}
