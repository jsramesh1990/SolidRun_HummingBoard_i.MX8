#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT
    
public:
    enum Level {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };
    Q_ENUM(Level)
    
    static Logger* instance();
    
    void log(Level level, const QString& message, const QString& file = "", int line = 0);
    
    void setLogFile(const QString& filename);
    void setLevel(Level level);
    
signals:
    void logMessage(Level level, const QString& message);
    
private:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
    
    static Logger* m_instance;
    QFile m_logFile;
    Level m_level;
    QMutex m_mutex;
    
    QString levelToString(Level level) const;
};

#define LOG_DEBUG(msg) Logger::instance()->log(Logger::Debug, msg, __FILE__, __LINE__)
#define LOG_INFO(msg) Logger::instance()->log(Logger::Info, msg, __FILE__, __LINE__)
#define LOG_WARNING(msg) Logger::instance()->log(Logger::Warning, msg, __FILE__, __LINE__)
#define LOG_ERROR(msg) Logger::instance()->log(Logger::Error, msg, __FILE__, __LINE__)
#define LOG_CRITICAL(msg) Logger::instance()->log(Logger::Critical, msg, __FILE__, __LINE__)

#endif // LOGGER_H
