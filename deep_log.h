#ifndef DEEP_LOG_H
#define DEEP_LOG_H

#include <QString>


class deep_log
{
public:
   // deep_log()=delete;
    deep_log(QString _filename);
    void write(const QString &str);
private:
    QString filename;
};

#endif // DEEP_LOG_H
