#include "dialogtemper.h"
#include "ui_dialogtemper.h"
#include <QSettings>


/*форма для определения операторов, приемки МО и температуры*/
DialogTemper::DialogTemper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTemper)
{
    ui->setupUi(this);
    //убрать знак вопроса
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    settings = new QSettings("settings.ini", QSettings::IniFormat);
//    /*dbg*/
//    //пишем по 2 значения в каждый список
//    QStringList lst = {"Ivanov","Petrov"};
//    QStringList lst1 = {"Ivanov1","Petrov1"};
//    QStringList lst2 = {"Ivanov2","Petrov2"};
//    settings->setValue("operators",lst);
//    settings->setValue("otk",lst1);
//    settings->setValue("vp_mo",lst2);
//    //
    //выгрузить данные на форму
    /*задать пустое поле*/
    QStringList operators = {""};
    QStringList otk = {""};
    QStringList vp_mo = {""};
    QStringList t = {""};
    /*считать из файла настроек*/
    operators += settings->value("operators").toStringList();
    otk += settings->value("otk").toStringList();
    vp_mo += settings->value("vp_mo").toStringList();
    t += settings->value("t").toStringList();
    /*Занести на форму*/
    ui->comboBox_operator->addItems(operators);
    ui->comboBox_otk->addItems(otk);
    ui->comboBox_vp_mo->addItems(vp_mo);
    ui->comboBox_temper->addItems(t);

}

DialogTemper::~DialogTemper()
{
    delete settings;
    delete ui;
}


void DialogTemper::on_comboBox_temper_currentTextChanged(const QString &arg1)
{
    QRegExp rx("-?(\\d{1,2})?");
       if (!rx.exactMatch(arg1)) {
           // Неверный ввод, удаляем последний символ
           QString currentText = ui->comboBox_temper->currentText();
           currentText.chop(1);
           ui->comboBox_temper->setCurrentText(currentText);
       } else {
           // Верный ввод, ничего не делаем
       }
}


void DialogTemper::on_pushButton_clicked()
{
    /*сигналы*/
    emit SetOperator(ui->comboBox_operator->currentText());
    emit SetOtk(ui->comboBox_otk->currentText());
    emit SetVPMO(ui->comboBox_vp_mo->currentText());
    emit SetTemper(ui->comboBox_temper->currentText());
    /*сохранить новые значения*/
    QStringList operators = settings->value("operators").toStringList();
    QStringList otk = settings->value("otk").toStringList();
    QStringList vp_mo = settings->value("vp_mo").toStringList();
    QStringList t = settings->value("t").toStringList();

    /*проверить, что значение не пустое и его ранее не было в списке*/
    /*оператор*/
    if(!ui->comboBox_operator->currentText().trimmed().isEmpty() && \
       !operators.contains(ui->comboBox_operator->currentText().trimmed()))
    {
        operators.append(ui->comboBox_operator->currentText().trimmed());
        settings->setValue("operators", operators);
    }

    /*отк*/
    if(!ui->comboBox_otk->currentText().trimmed().isEmpty() && \
       !otk.contains(ui->comboBox_otk->currentText().trimmed()))
    {
        otk.append(ui->comboBox_otk->currentText().trimmed());
        settings->setValue("otk", otk);
    }

    /*вп мо*/
    if(!ui->comboBox_vp_mo->currentText().trimmed().isEmpty() && \
       !vp_mo.contains(ui->comboBox_vp_mo->currentText().trimmed()))
    {
        vp_mo.append(ui->comboBox_vp_mo->currentText().trimmed());
        settings->setValue("vp_mo", vp_mo);
    }

    /*температура*/
    if(!ui->comboBox_temper->currentText().trimmed().isEmpty() && \
       !t.contains(ui->comboBox_temper->currentText().trimmed()))
    {
        t.append(ui->comboBox_temper->currentText().trimmed());
        settings->setValue("t", t);
    }

    /*Закрыть окно*/
    close();
}

