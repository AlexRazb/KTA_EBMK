#ifndef DIALOGTEMPER_H
#define DIALOGTEMPER_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DialogTemper;
}

class DialogTemper : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTemper(QWidget *parent = nullptr);
    ~DialogTemper();

private slots:
    void on_comboBox_temper_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::DialogTemper *ui;
    QSettings *settings;

signals:
    /*Сигналы для передачи в другою форму данных*/
    void SetOperator(QString str);
    void SetOtk(QString str);
    void SetVPMO(QString str);
    void SetTemper(QString str);
};

#endif // DIALOGTEMPER_H
