#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>

class StyleHelper
{
public:
    static QString getStartButtonsStyleUnSet();
    static QString getStartButtonsStyleSet();
    static QString getCheckBoxSettings();//подключение ресурсов при включении или выключении чекбокса
    static QString getTestButtonStyle();//кнопки с названиями тестов

    /*Кнопки состояния теста*/
    static QString getStatusButtonStyleYes();//Успешный тест
    static QString getStatusButtonStyleNo();//Отказ теста
    static QString getStatusButtonStyleClear();//Очистить статус
    static QString getStatusButtonStyleInProcess();//Тест выполняется

    /*Кнопки старт, сохранить...*/
    static QString getMainButtonStyle();
};

#endif // STYLEHELPER_H
