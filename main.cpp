#include "mainwindow.h"
#include "dialogtemper.h"
#include "usbhiddevice.h"

#include <QApplication>
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*usb*/
    QMessageBox msgBox;

    USBHIDDevice USB;
    USB.open(0x03fd,0x0300);
    if(USB.IsOpened())
    {
        msgBox.setWindowTitle("Пример");
        msgBox.setText("USB открыт и готов к работе");
        msgBox.exec();
    }
    else
    {
        msgBox.setWindowTitle("Пример");
        msgBox.setText("не удалось открыть USB");
        msgBox.exec();
        //return 1;
    }


    /*класс создается раньше, тк необходимо создать связь сигнал->слот*/
    MainWindow w;
    // Окно с температурой и оператором
    DialogTemper* dialog = new DialogTemper;
    /*Настроить сигнал-слот*/
    QObject::connect(dialog, &DialogTemper::SetOperator, &w, &MainWindow::OnSetOperator);
    QObject::connect(dialog, &DialogTemper::SetOtk, &w, &MainWindow::OnSetOtk);
    QObject::connect(dialog, &DialogTemper::SetVPMO, &w, &MainWindow::OnSetVPMO);
    QObject::connect(dialog, &DialogTemper::SetTemper, &w, &MainWindow::OnSetTemper);

    dialog->setModal(true);
    dialog->exec();
    delete dialog;

    /*Проверить соединение по usb, вывести окно типа "Устройство usb не обнаружено, убедитель, что устройство с VID... PID... подключено"*/
    /*Тркп перевести в режим КТА для всех модулей(добавить структуру общую для всех ТРКП МУ-1 (Канал управления)(Канал индикации))*/
    /*Выходные РК и АС в логический 0 и в 0В соответственно...По окончанию работы программы все также в 0*/
    //MainWindow w;
    w.show();
    return a.exec();
}
