#include "deep_log.h"
#include <QString>
#include <QTime>

deep_log::deep_log(QString _filename)
{
    filename = _filename;
    /*Открыть файл с именем и очистить полностью*/
    FILE *pFile=fopen(qPrintable(filename), "w+");
    if(!pFile)
    {
        fclose(pFile);
    }
}

void deep_log::write(const QString &str)
{
    /*Запись в лог файл строки*/
    QTime currTime = QTime::currentTime();
    QString timeText = currTime.toString("hh:mm:ss.zzz");
    QString buf;
    buf=timeText+" "+str+"\n";
    // Лог-файл открывается в режиме добавления данных
    FILE *pFile=fopen(qPrintable(filename), "a+");
    fprintf(pFile, "%s", qPrintable(buf));
    fclose(pFile);
}
