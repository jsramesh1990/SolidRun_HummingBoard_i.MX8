#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QObject>
#include <QTimer>
#include <QVector>

struct SystemStats {
    double cpuUsage;
    double memoryUsage;
    double diskUsage;
    double temperature;
    QString kernelVersion;
    QString ipAddress;
    int uptime;
};

class SystemMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SystemStats stats READ stats NOTIFY statsChanged)
    Q_PROPERTY(bool monitoring READ monitoring WRITE setMonitoring NOTIFY monitoringChanged)
    
public:
    explicit SystemMonitor(QObject *parent = nullptr);
    ~SystemMonitor();
    
    SystemStats stats() const { return m_stats; }
    bool monitoring() const { return m_monitoring; }
    void setMonitoring(bool enabled);
    
    Q_INVOKABLE void refresh();
    
signals:
    void statsChanged();
    void monitoringChanged();
    void alert(const QString &message);
    
private slots:
    void updateStats();
    
private:
    SystemStats m_stats;
    QTimer *m_timer;
    bool m_monitoring;
    
    double getCpuUsage();
    double getMemoryUsage();
    double getDiskUsage();
    double getTemperature();
    QString getKernelVersion();
    QString getIpAddress();
    int getUptime();
};

Q_DECLARE_METATYPE(SystemStats)

#endif // SYSTEMMONITOR_H
