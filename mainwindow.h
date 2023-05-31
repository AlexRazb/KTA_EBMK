#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QMovie>
#include "teststhread.h"
#include <QListWidgetItem>

#define KOM 0
#define IND 1

//данная конструкция используется для передачи данных между сигналами и слотами, так как входной параметр может быть только 1
//typedef struct IndexOfModuleAndIndexOfTest
//{
//    qint8 indexOfModule;//индекс модуля
//    qint8 indexOfTest;//индекс теста
//} IndexOfModuleAndIndexOfTest;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /*Слоты для взаимодействия с формой установки температуры и тд*/
    void OnSetOperator(QString str);
    void OnSetOtk(QString str);
    void OnSetVPMO(QString str);
    void OnSetTemper(QString str);

    /*Слоты для взаимодействия с потоковым классом*/
    /*слот для окраса кнопки в зеленый(успех теста)
        старший байт - индекс тестируемой подгруппы ЭБМК-0, МУ1-1, УП-2
        младший байт - индекс теста для выставления результата*/
    void PaintButtonToGreen(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);

    /*слот для окраса кнопки в красный(отказ теста)
        старший байт - индекс тестируемой подгруппы ЭБМК-0, МУ1-1, УП-2
        младший байт - индекс теста для выставления результата*/
    void PaintButtonToRed(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);

    /*слот для окраса кнопки в белый(станов теста)
        старший байт - индекс тестируемой подгруппы ЭБМК-0, МУ1-1, УП-2
        младший байт - индекс теста для выставления результата*/
    void PaintButtonToWhite(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);

    /*слот для окраса кнопки в анимацию(работа теста)
        старший байт - индекс тестируемой подгруппы ЭБМК-0, МУ1-1, УП-2
        младший байт - индекс теста для выставления результата*/
    void PaintButtonToGif(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);

    /*Функция для вывода в лист элемента*/
    void addItemToList(QString str);

    /*Функция для вывода в лист элемента(С ошибкой)*/
    void addItemToListErr(QString str);

    /*Слот для срабатывания по окончанию работы потока*/
    void onThreadFineshed();

    /*Слот для печати в pdf*/
    void onPrintPdf();
    /**/
signals:
    /*сигнал для остановки работы потока*/
    void SetStop(bool stop_status);
    /*сигнал, что элемент добавлен в список*/
    void ItemAdded();

    /*сигнал нажатия на кнопку теста и поиск*/
    void FindInList(QString str);

private slots:

    /*Поиск и выделение следующей строки в списке (поиск по тестам)*/
    void FindAndSelectNextItemInList(QString str);

    /*Обработка изменения скролл бара для "примагничивания"*/
    void onUserMove(int position);
    void onItemAdded();

    void on_pushButton_EBMK_clicked();

    void on_pushButton_MU1_clicked();

    void on_pushButton_UP_clicked();

    void on_pushButton_RK_clicked();

    void on_pushButton_about_clicked();

    void on_checkBox_EBMK_All_clicked();

    void on_checkBox_MU1_All_clicked();

    void on_checkBox_UP_All_clicked();

    void on_checkBox_EBMK_MIEA_clicked();

    void on_checkBox_EBMK_ASV_SIN_Kom_clicked();

    void on_checkBox_EBMK_ASV_SIN_Ind_clicked();

    void on_checkBox_EBMK_ASV_Kom_clicked();

    void on_checkBox_EBMK_15V_clicked();

    void on_checkBox_EBMK_PRIBL_Kom_clicked();

    void on_checkBox_EBMK_PRIBL_Ind_clicked();

    void on_checkBox_EBMK_ASP_SKVT_Kom_clicked();

    void on_checkBox_EBMK_ASP_SKVT_Ind_clicked();

    void on_checkBox_EBMK_DAVL_Kom_clicked();

    void on_checkBox_EBMK_RKP_0_28_Kom_clicked();

    void on_checkBox_EBMK_RKP_0_28_Ind_clicked();

    void on_checkBox_MU1_MIEA_clicked();

    void on_checkBox_MU1_ASV_SIN_Kom_clicked();

    void on_checkBox_MU1_ASV_SIN_Ind_clicked();

    void on_checkBox_MU1_ASV_Kom_clicked();

    void on_checkBox_MU1_PRIBL_Kom_clicked();

    void on_checkBox_MU1_PRIBL_Ind_clicked();

    void on_checkBox_MU1_ASP_SKVT_Kom_clicked();

    void on_checkBox_MU1_ASP_SKVT_Ind_clicked();

    void on_checkBox_MU1_ASP_Kom_clicked();

    void on_checkBox_MU1_ASP_Ind_clicked();

    void on_checkBox_MU1_DAVL_Kom_clicked();

    void on_checkBox_MU1_RKP_0_28_Kom_clicked();

    void on_checkBox_MU1_RKP_0_28_Ind_clicked();

    void on_checkBox_MU1_RKP_28_Kom_clicked();

    void on_checkBox_MU1_RKP_28_Ind_clicked();

    void on_checkBox_MU1_RKV_TTL_Ind_clicked();

    void on_checkBox_MU1_RKP_TTL_Kom_clicked();

    void on_checkBox_MU1_RKP_TTL_Ind_clicked();

    void on_checkBox_MU1_OUT_PWM_Kom_clicked();

    void on_checkBox_MU1_OZU_clicked();

    void on_checkBox_MU1_PZU_clicked();

    void on_checkBox_MU1_REGISTRATOR_clicked();

    void on_checkBox_UP_15V_clicked();

    void on_checkBox_UP_KRKV_Kom_clicked();

    void on_checkBox_UP_KRKV_Ind_clicked();

    void on_checkBox_UP_OUT_PWM_Kom_clicked();

    void on_checkBox_UP_RKP_TTL_Kom_clicked();

    void on_checkBox_UP_RKP_TTL_Ind_clicked();

    void on_checkBox_UP_ASP_Kom_clicked();

    void on_checkBox_UP_ASP_Ind_clicked();

    void on_checkBox_UP_OUT_PWM_EXO_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Start_Stop_clicked();

    void on_pushButton_MU1_MIEA_clicked();

    void on_pushButton_MU1_ASV_SIN_Kom_clicked();

    void on_pushButton_EBMK_MIEA_clicked();

    void on_pushButton_EBMK_ASV_SIN_Kom_clicked();

    void on_pushButton_EBMK_ASV_SIN_Ind_clicked();

    void on_pushButton_EBMK_ASV_Kom_clicked();

    void on_pushButton_EBMK_15V_clicked();

    void on_pushButton_EBMK_PRIBL_Kom_clicked();

    void on_pushButton_EBMK_PRIBL_Ind_clicked();

    void on_pushButton_EBMK_ASP_SKVT_Kom_clicked();

    void on_pushButton_EBMK_ASP_SKVT_Ind_clicked();

    void on_pushButton_EBMK_DAVL_Kom_clicked();

    void on_pushButton_EBMK_RKP_0_28_Kom_clicked();

    void on_pushButton_EBMK_RKP_0_28_Ind_clicked();

    void on_pushButton_MU1_ASV_SIN_Ind_clicked();

    void on_pushButton_MU1_ASV_Kom_clicked();

    void on_pushButton_MU1_PRIBL_Kom_clicked();

    void on_pushButton_MU1_PRIBL_Ind_clicked();

    void on_pushButton_MU1_ASP_SKVT_Kom_clicked();

    void on_pushButton_MU1_ASP_SKVT_Ind_clicked();

    void on_pushButton_MU1_ASP_Kom_clicked();

    void on_pushButton_MU1_ASP_Ind_clicked();

    void on_pushButton_MU1_DAVL_Kom_clicked();

    void on_pushButton_MU1_RKP_0_28_Kom_clicked();

    void on_pushButton_MU1_RKP_0_28_Ind_clicked();

    void on_pushButton_MU1_RKP_28_Kom_clicked();

    void on_pushButton_MU1_RKP_28_Ind_clicked();

    void on_pushButton_MU1_RKV_TTL_Ind_clicked();

    void on_pushButton_MU1_RKP_TTL_Kom_clicked();

    void on_pushButton_MU1_RKP_TTL_Ind_clicked();

    void on_pushButton_MU1_OUT_PWM_Kom_clicked();

    void on_pushButton_MU1_OZU_clicked();

    void on_pushButton_MU1_PZU_clicked();

    void on_pushButton_MU1_REGISTRATOR_clicked();

    void on_pushButton_UP_15V_clicked();

    void on_pushButton_UP_KRKV_Kom_clicked();

    void on_pushButton_UP_KRKV_Ind_clicked();

    void on_pushButton_UP_OUT_PWM_Kom_clicked();

    void on_pushButton_UP_RKP_TTL_Kom_clicked();

    void on_pushButton_UP_RKP_TTL_Ind_clicked();

    void on_pushButton_UP_ASP_Kom_clicked();

    void on_pushButton_UP_ASP_Ind_clicked();

    void on_pushButton_UP_OUT_PWM_EXO_clicked();

private:
    Ui::MainWindow *ui;
    void SetActiveButton(int num);
    /*функция для установки свойств выбранной группе кнопок тестов*/
    void SetStyleForTestButtons(QVector<QPushButton*> *vec);
    /*функция для установки свойств выбранной группе кнопок тестов*/
    void SetStyleForStatusButtons(QVector<QPushButton*> *vec);
    /*функция для установки свойств выбранной группе чекбоксов*/
    void SetStyleForChecks(QVector<QCheckBox*> *vec);

    /*Ниже определены векторы для удобства итерации по элементам формы*/
    QVector<QPushButton*> EBMK_tests_buttons;
    QVector<QPushButton*> MU1_tests_buttons;
    QVector<QPushButton*> UP_tests_buttons;

    /*кнопки состояния вкладка ЭБМК*/
    QVector<QPushButton*> EBMK_status_buttons;
    QVector<QPushButton*> MU1_status_buttons;
    QVector<QPushButton*> UP_status_buttons;

    /*чекбоксы тестов вкладка ЭБМК*/
    QVector<QCheckBox*> EBMK_tests_checks;
    QVector<QCheckBox*> MU1_tests_checks;
    QVector<QCheckBox*> UP_tests_checks;

    /*лейблы с загрузкой*/
    QVector<QLabel*> EBMK_status_labels;
    QVector<QLabel*> MU1_status_labels;
    QVector<QLabel*> UP_status_labels;

    /*Вектор имен подмодулей тестирования*/
    QVector<QString> Module_names_rus_short = {"ЭБМК","МУ-1","Устр. питания"};
    QVector<QString> Module_names_eng_short = {"EBMK","MU-1","UP"};
    QVector<QString> Module_names_rus_full = {"Электронный блок управления механизацией крыла ЭБМК-1","Модуль управления MU-1","Устройство питания"};

    /*Анализ всех чекбоксов и выставление галочки "все"*/
    void AccumulateAndSetAllCheckBoxes();

    /*Функция помечает строку в лист виджете как ошибку*/
    void SetStringInListAsError();

    /*Функция очистки записей и результатов тестирования*/
    void ClearAllData();

    //заблокировать или разблокировать все кнопки на время выполнения теста
    void SetEnableStatusForAllButtons(bool status);

    /*Функция получает индекс( с 0) текущей активной вкладки табвиджета*/
    quint8 GetCurrentTabIndex();

    qint8 currentTab = 0;//текущее состояние табвиджета

    TestsThread *Tests;

    //признак, что поток с тестами запущен
    bool is_thread_running;

    bool scroll_helper;//признак "подтягивания списка к низу"

    QMovie movie;

    QString _operator;
    QString _otk;
    QString _vpmo;
    QString _temper;



};
#endif // MAINWINDOW_H
