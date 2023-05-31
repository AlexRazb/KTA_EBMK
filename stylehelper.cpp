#include "stylehelper.h"



QString StyleHelper::getStartButtonsStyleUnSet()
{
    return "QPushButton{"
           "color:#fff;"
           "background: none;"
           "border: none;"
          // "background-color:#6D7BFB"
            "background-color:#89c0e8"
           "}";
}

QString StyleHelper::getStartButtonsStyleSet()
{
    return "QPushButton{"
           "color:#fff;"
           "background: none;"
           "border: none;"
          // "background-color:#818DFC"
            "background-color:#4ca3e0"
           "}";
}

QString StyleHelper::getCheckBoxSettings()
{
    return "QCheckBox::indicator { "
           "width:20px; height: 20px;"
           "} "
           "QCheckBox::indicator::checked {"
           "image: url(:/resourses/checkbox_check.png);"
           "} "
           "QCheckBox::indicator::unchecked {"
           "image: url(:/resourses/checkbox_uncheck.png);"
           "}";
}

QString StyleHelper::getTestButtonStyle()
{

    return "QPushButton{"
           "color:#fff;"
           "background: none;"
           "border: none;"
           "border-radius:5px;"
           "font-size: 14px;"
           "padding: 400px 240px;"
           "background-color:#2991DB"
           "}";

}

QString StyleHelper::getStatusButtonStyleYes()
{
    return "QPushButton{"
           "border:1px solid #333;"
           "border-radius:5px;"
           "background-color:#35EA2E"
           "}";
}

QString StyleHelper::getStatusButtonStyleNo()
{
    return "QPushButton{"
           "border:1px solid #333;"
           "border-radius:5px;"
           "background-color:#EA442E"
           "}";
}

QString StyleHelper::getStatusButtonStyleClear()
{
    return "QPushButton{"
         //  "color:#fff;"
            "border:1px solid #333;"
         //  "background: none;"
         //  "border: none;"
           "border-radius:5px;"
           "background-color:#fff"
           "}";
}

QString StyleHelper::getStatusButtonStyleInProcess()
{
    return "QPushButton{"
         //  "color:#fff;"
            "border:1px solid #333;"
         //  "background: none;"
         //  "border: none;"
           "border-radius:5px;"
           "background-color:#fff"
           "}";
}

QString StyleHelper::getMainButtonStyle()
{
    return "QPushButton{"
           "color:#fff;"
            "background: none;"
            //"border: none;"
            "border:2px solid #333;"
            "border-radius:5px;"
            "background-color: #2991DB;"
          //  "font-family: 'Roboto Medium';"
        //    "font-size:16px;"
           "}"
    "QPushButton::hover{"
      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(73, 172, 248, 255), stop:1 rgba(85, 215, 255, 255))"
    "}"
    "QPushButton::pressed{"
    "background-color: #2991DB;"

           "}";
}


