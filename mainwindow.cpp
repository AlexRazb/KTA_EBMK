#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>
#include "stylehelper.h"
#include "deep_log.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDateTime>
#include "teststhread.h"
#include <QObject>
#include <QScrollBar>
#include "test_names.h"
#include <QListWidgetItem>
#include <algorithm>

#include <QTextDocument>
#include <QPrinter>

deep_log log("debug.txt");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();//скрыть вкладки таббара
    ui->tabWidget->setCurrentIndex(0);//base index
    currentTab = GetCurrentTabIndex();
    ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
    ui->pushButton_otstup->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_otstup1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
    ui->pushButton_Start_Stop->setStyleSheet(StyleHelper::getMainButtonStyle());
    ui->pushButton_Clear->setStyleSheet(StyleHelper::getMainButtonStyle());
    ui->pushButton_Save->setStyleSheet(StyleHelper::getMainButtonStyle());
    ui->checkBox_cycle->setStyleSheet(StyleHelper::getCheckBoxSettings());


    /*Установить стиль для чекбоксов ВСЕ*/
    ui->checkBox_EBMK_All->setStyleSheet(StyleHelper::getCheckBoxSettings());
    ui->checkBox_MU1_All->setStyleSheet(StyleHelper::getCheckBoxSettings());
    ui->checkBox_UP_All->setStyleSheet(StyleHelper::getCheckBoxSettings());

    /*раскидать кнопки по массивам*/
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_MIEA);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_ASV_SIN_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_ASV_SIN_Ind);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_ASV_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_15V);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_PRIBL_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_PRIBL_Ind);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_ASP_SKVT_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_ASP_SKVT_Ind);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_DAVL_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_RKP_0_28_Kom);
    EBMK_tests_buttons.push_back(ui->pushButton_EBMK_RKP_0_28_Ind);


    EBMK_status_buttons.push_back(ui->pushButton_EBMK_MIEA_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_ASV_SIN_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_ASV_SIN_Ind_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_ASV_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_15V_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_PRIBL_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_PRIBL_Ind_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_ASP_SKVT_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_ASP_SKVT_Ind_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_DAVL_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_RKP_0_28_Kom_status);
    EBMK_status_buttons.push_back(ui->pushButton_EBMK_RKP_0_28_Ind_status);


    EBMK_tests_checks.push_back(ui->checkBox_EBMK_MIEA);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_ASV_SIN_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_ASV_SIN_Ind);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_ASV_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_15V);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_PRIBL_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_PRIBL_Ind);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_ASP_SKVT_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_ASP_SKVT_Ind);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_DAVL_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_RKP_0_28_Kom);
    EBMK_tests_checks.push_back(ui->checkBox_EBMK_RKP_0_28_Ind);

    /*Выставить стартовыее значения*/
    /*Кнопки тестов*/
    SetStyleForTestButtons(&EBMK_tests_buttons);
    /*Кнопки состояния*/
    SetStyleForStatusButtons(&EBMK_status_buttons);
    /*Чекбоксы*/
    SetStyleForChecks(&EBMK_tests_checks);

    /*раскидать кнопки по векторам МУ-1*/
    MU1_tests_buttons.push_back(ui->pushButton_MU1_MIEA);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASV_SIN_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASV_SIN_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASV_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_PRIBL_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_PRIBL_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASP_SKVT_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASP_SKVT_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASP_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_ASP_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_DAVL_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_0_28_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_0_28_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_28_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_28_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKV_TTL_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_TTL_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_RKP_TTL_Ind);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_OUT_PWM_Kom);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_OZU);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_PZU);
    MU1_tests_buttons.push_back(ui->pushButton_MU1_REGISTRATOR);


    MU1_status_buttons.push_back(ui->pushButton_MU1_MIEA_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASV_SIN_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASV_SIN_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASV_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_PRIBL_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_PRIBL_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASP_SKVT_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASP_SKVT_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASP_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_ASP_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_DAVL_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_0_28_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_0_28_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_28_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_28_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKV_TTL_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_TTL_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_RKP_TTL_Ind_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_OUT_PWM_Kom_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_OZU_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_PZU_status);
    MU1_status_buttons.push_back(ui->pushButton_MU1_REGISTRATOR_status);


    MU1_tests_checks.push_back(ui->checkBox_MU1_MIEA);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASV_SIN_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASV_SIN_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASV_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_PRIBL_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_PRIBL_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASP_SKVT_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASP_SKVT_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASP_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_ASP_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_DAVL_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_0_28_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_0_28_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_28_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_28_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKV_TTL_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_TTL_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_RKP_TTL_Ind);
    MU1_tests_checks.push_back(ui->checkBox_MU1_OUT_PWM_Kom);
    MU1_tests_checks.push_back(ui->checkBox_MU1_OZU);
    MU1_tests_checks.push_back(ui->checkBox_MU1_PZU);
    MU1_tests_checks.push_back(ui->checkBox_MU1_REGISTRATOR);

    /*Выставить стартовыее значения*/
    /*Кнопки тестов*/
    SetStyleForTestButtons(&MU1_tests_buttons);
    /*Кнопки состояния*/
    SetStyleForStatusButtons(&MU1_status_buttons);
    /*Чекбоксы*/
    SetStyleForChecks(&MU1_tests_checks);

    /*раскидать кнопки по векторам Устройство питания*/
    UP_tests_buttons.push_back(ui->pushButton_UP_15V);
    UP_tests_buttons.push_back(ui->pushButton_UP_KRKV_Kom);
    UP_tests_buttons.push_back(ui->pushButton_UP_KRKV_Ind);
    UP_tests_buttons.push_back(ui->pushButton_UP_OUT_PWM_Kom);
    UP_tests_buttons.push_back(ui->pushButton_UP_RKP_TTL_Kom);
    UP_tests_buttons.push_back(ui->pushButton_UP_RKP_TTL_Ind);
    UP_tests_buttons.push_back(ui->pushButton_UP_ASP_Kom);
    UP_tests_buttons.push_back(ui->pushButton_UP_ASP_Ind);
    UP_tests_buttons.push_back(ui->pushButton_UP_OUT_PWM_EXO);


    UP_status_buttons.push_back(ui->pushButton_UP_15V_status);
    UP_status_buttons.push_back(ui->pushButton_UP_KRKV_Kom_status);
    UP_status_buttons.push_back(ui->pushButton_UP_KRKV_Ind_status);
    UP_status_buttons.push_back(ui->pushButton_UP_OUT_PWM_Kom_status);
    UP_status_buttons.push_back(ui->pushButton_UP_RKP_TTL_Kom_status);
    UP_status_buttons.push_back(ui->pushButton_UP_RKP_TTL_Ind_status);
    UP_status_buttons.push_back(ui->pushButton_UP_ASP_Kom_status);
    UP_status_buttons.push_back(ui->pushButton_UP_ASP_Ind_status);
    UP_status_buttons.push_back(ui->pushButton_UP_OUT_PWM_EXO_status);


    UP_tests_checks.push_back(ui->checkBox_UP_15V);
    UP_tests_checks.push_back(ui->checkBox_UP_KRKV_Kom);
    UP_tests_checks.push_back(ui->checkBox_UP_KRKV_Ind);
    UP_tests_checks.push_back(ui->checkBox_UP_OUT_PWM_Kom);
    UP_tests_checks.push_back(ui->checkBox_UP_RKP_TTL_Kom);
    UP_tests_checks.push_back(ui->checkBox_UP_RKP_TTL_Ind);
    UP_tests_checks.push_back(ui->checkBox_UP_ASP_Kom);
    UP_tests_checks.push_back(ui->checkBox_UP_ASP_Ind);
    UP_tests_checks.push_back(ui->checkBox_UP_OUT_PWM_EXO);

    /*Выставить стартовыее значения Устройство питания*/
    /*Кнопки тестов*/
    SetStyleForTestButtons(&UP_tests_buttons);
    /*Кнопки состояния*/
    SetStyleForStatusButtons(&UP_status_buttons);
    /*Чекбоксы*/
    SetStyleForChecks(&UP_tests_checks);

    /*настройка лейблов загрузочных(для проигрывания гиф*/
    EBMK_status_labels.push_back(ui->label_EBMK_MIEA_status);
    EBMK_status_labels.push_back(ui->label_EBMK_ASV_SIN_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_ASV_SIN_Ind_status);
    EBMK_status_labels.push_back(ui->label_EBMK_ASV_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_15V_status);
    EBMK_status_labels.push_back(ui->label_EBMK_PRIBL_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_PRIBL_Ind_status);
    EBMK_status_labels.push_back(ui->label_EBMK_ASP_SKVT_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_ASP_SKVT_Ind_status);
    EBMK_status_labels.push_back(ui->label_EBMK_DAVL_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_RKP_0_28_Kom_status);
    EBMK_status_labels.push_back(ui->label_EBMK_RKP_0_28_Ind_status);


    MU1_status_labels.push_back(ui->label_MU1_MIEA_status);
    MU1_status_labels.push_back(ui->label_MU1_ASV_SIN_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_ASV_SIN_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_ASV_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_PRIBL_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_PRIBL_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_ASP_SKVT_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_ASP_SKVT_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_ASP_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_ASP_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_DAVL_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_0_28_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_0_28_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_28_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_28_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_RKV_TTL_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_TTL_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_RKP_TTL_Ind_status);
    MU1_status_labels.push_back(ui->label_MU1_OUT_PWM_Kom_status);
    MU1_status_labels.push_back(ui->label_MU1_OZU_status);
    MU1_status_labels.push_back(ui->label_MU1_PZU_status);
    MU1_status_labels.push_back(ui->label_MU1_REGISTRATOR_status);


    UP_status_labels.push_back(ui->label_UP_15V_status);
    UP_status_labels.push_back(ui->label_UP_KRKV_Kom_status);
    UP_status_labels.push_back(ui->label_UP_KRKV_Ind_status);
    UP_status_labels.push_back(ui->label_UP_OUT_PWM_Kom_status);
    UP_status_labels.push_back(ui->label_UP_RKP_TTL_Kom_status);
    UP_status_labels.push_back(ui->label_UP_RKP_TTL_Ind_status);
    UP_status_labels.push_back(ui->label_UP_ASP_Kom_status);
    UP_status_labels.push_back(ui->label_UP_ASP_Ind_status);
    UP_status_labels.push_back(ui->label_UP_OUT_PWM_EXO_status);

    /*очистить все лейблы*/
    for(auto &i:EBMK_status_labels)
    {
        i->clear();
    }

    for(auto &i:MU1_status_labels)
    {
        i->clear();
    }

    for(auto &i:UP_status_labels)
    {
        i->clear();
    }

    //признак, что поток с тестами запущен. сброс признака
    is_thread_running = 0;

    Tests = new TestsThread(0,ui->checkBox_cycle, &EBMK_tests_checks,&MU1_tests_checks,&UP_tests_checks);

    /*сигналы и слоты*/
    /*связать Ок теста*/
    QObject::connect(Tests, &TestsThread::Ok, this, &MainWindow::PaintButtonToGreen);
    /*связать ошибку теста*/
    QObject::connect(Tests, &TestsThread::Err, this, &MainWindow::PaintButtonToRed);
    /*связать очистку теста*/
    QObject::connect(Tests, &TestsThread::Clear, this, &MainWindow::PaintButtonToWhite);
    /*связать загрузку теста*/
    QObject::connect(Tests, &TestsThread::Load, this, &MainWindow::PaintButtonToGif);

    /*Вывод сообщений в листбокс*/
    QObject::connect(Tests, &TestsThread::Print, this, &MainWindow::addItemToList);
    QObject::connect(Tests, &TestsThread::PrintErr, this, &MainWindow::addItemToListErr);

    /*остановка потока с тестами*/
    QObject::connect(this, &MainWindow::SetStop, Tests, &TestsThread::SetStop);

    /*Добавить "Магнит" на лист бокс
    по умолчанию вкл, при прокрутке до конца вкл, при перелистывании выкл*/

    // Включение автоматической прокрутки при добавлении элементов в список
    scroll_helper = true;

    /*Обработка положения скролл бара*/
    connect(ui->listWidget->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::onUserMove);
    connect(this, &MainWindow::ItemAdded, this, &MainWindow::onItemAdded);

    /*Поток закончил работу*/
    connect(Tests, &TestsThread::finished, this, &MainWindow::onThreadFineshed);

    /*Печать в пдф*/
    QObject::connect(Tests, &TestsThread::Pdf, this, &MainWindow::onPrintPdf);

    /*Поиск строки в списке*/
    connect(this, &MainWindow::FindInList, this, &MainWindow::FindAndSelectNextItemInList);

    movie.setFileName(":/resourses/loading.gif");

     _operator = "";
     _otk = "";
     _vpmo = "";
     _temper = "";

}

MainWindow::~MainWindow()
{
    /*Остановка при закрытии окна*/
    emit SetStop(true);
    /*ждать остановки работы потока*/
    Tests->wait();
    delete Tests;
    delete ui;
}

void MainWindow::OnSetOperator(QString str)
{
    _operator = str;
}

void MainWindow::OnSetOtk(QString str)
{
    _otk = str;
}

void MainWindow::OnSetVPMO(QString str)
{
    _vpmo = str;
}

void MainWindow::OnSetTemper(QString str)
{
    _temper = str;
}


//слот закраски кнопки в зеленый цвет(успешный тест)
void MainWindow::PaintButtonToGreen(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index)
{
    quint8 curTab = (HI_byte_is_tab_index_LOW_byte_is_test_index >> 8) & 0xFF;
    quint8 curTest = HI_byte_is_tab_index_LOW_byte_is_test_index & 0xFF;
    QVector<QPushButton*>* curButtons = nullptr;//указатель на вектор кнопок состояния на текущей вкладке
    QVector<QLabel*>* curLabel = nullptr;//указатель на вектор лейблов загрузки
    switch (curTab) {
    case 0: curButtons = &EBMK_status_buttons; curLabel = &EBMK_status_labels; break;
    case 1: curButtons = &MU1_status_buttons; curLabel = &MU1_status_labels; break;
    case 2: curButtons = &UP_status_buttons; curLabel = &UP_status_labels; break;
    default:break;
    }
    if (curButtons)
    {
        movie.stop();//остановить анимацию
        curLabel->at(curTest)->clear();//очистить лейбл
        curButtons->at(curTest)->setStyleSheet(StyleHelper::getStatusButtonStyleYes());
    }

}

void MainWindow::PaintButtonToRed(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index)
{
    quint8 curTab = (HI_byte_is_tab_index_LOW_byte_is_test_index >> 8) & 0xFF;
    quint8 curTest = HI_byte_is_tab_index_LOW_byte_is_test_index & 0xFF;
    QVector<QPushButton*>* curButtons = nullptr;//указатель на вектор кнопок состояния на текущей вкладке
    QVector<QLabel*>* curLabel = nullptr;//указатель на вектор лейблов загрузки
    switch (curTab) {
    case 0: curButtons = &EBMK_status_buttons; curLabel = &EBMK_status_labels; break;
    case 1: curButtons = &MU1_status_buttons; curLabel = &MU1_status_labels; break;
    case 2: curButtons = &UP_status_buttons; curLabel = &UP_status_labels; break;
    default:break;
    }
    if (curButtons)
    {
        movie.stop();//остановить анимацию
        curLabel->at(curTest)->clear();//очистить лейбл
        curButtons->at(curTest)->setStyleSheet(StyleHelper::getStatusButtonStyleNo());
    }
}

void MainWindow::PaintButtonToWhite(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index)
{
    quint8 curTab = (HI_byte_is_tab_index_LOW_byte_is_test_index >> 8) & 0xFF;
    quint8 curTest = HI_byte_is_tab_index_LOW_byte_is_test_index & 0xFF;
    QVector<QPushButton*>* curButtons = nullptr;//указатель на вектор кнопок состояния на текущей вкладке
    QVector<QLabel*>* curLabel = nullptr;//указатель на вектор лейблов загрузки
    switch (curTab) {
    case 0: curButtons = &EBMK_status_buttons; curLabel = &EBMK_status_labels; break;
    case 1: curButtons = &MU1_status_buttons; curLabel = &MU1_status_labels; break;
    case 2: curButtons = &UP_status_buttons; curLabel = &UP_status_labels; break;
    default:break;
    }
    if (curButtons)
    {
        movie.stop();//остановить анимацию
        curLabel->at(curTest)->clear();//очистить лейбл
        curButtons->at(curTest)->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
    }
}

/*установить на картинку иммитацию загрузки(гиф)*/
void MainWindow::PaintButtonToGif(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index)
{
    quint8 curTab = (HI_byte_is_tab_index_LOW_byte_is_test_index >> 8) & 0xFF;
    quint8 curTest = HI_byte_is_tab_index_LOW_byte_is_test_index & 0xFF;
    QVector<QPushButton*>* curButtons = nullptr;//указатель на вектор кнопок состояния на текущей вкладке
    QVector<QLabel*>* curLabel = nullptr;//указатель на вектор лейблов загрузки
    switch (curTab) {
    case 0: curButtons = &EBMK_status_buttons; curLabel = &EBMK_status_labels; break;
    case 1: curButtons = &MU1_status_buttons; curLabel = &MU1_status_labels; break;
    case 2: curButtons = &UP_status_buttons; curLabel = &UP_status_labels; break;
    default:break;
    }
    if (curButtons)
    {
        curButtons->at(curTest)->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
        curLabel->at(curTest)->setMovie(&movie);
        movie.start();//остановить анимацию

    }

}

/*слот вывода строки в лист*/
void MainWindow::addItemToList(QString str)
{
    ui->listWidget->addItem(str);
    emit ItemAdded();
}

/*слот вывода строки в лист(с ошибкой)*/
void MainWindow::addItemToListErr(QString str)
{
    ui->listWidget->addItem(str);
    SetStringInListAsError();
    emit ItemAdded();
}

void MainWindow::onThreadFineshed()
{
    //поток закончил работу
    is_thread_running = false;
    //задать имя кнопке
    ui->pushButton_Start_Stop->setText("Старт");
    //разблокировать все кнопки и удалить подсказки
    SetEnableStatusForAllButtons(true);
}

/*печать в пдф*/
void MainWindow::onPrintPdf()
{
    /*если не стоит цикл и вп-мо указан, то печатать*/
    if(!ui->checkBox_cycle->isChecked() && !_vpmo.isEmpty())
    {
        QDateTime date = QDateTime::currentDateTime();
        QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
        QString filename;
        QString data;//данные из листа
        filename = Module_names_eng_short[GetCurrentTabIndex()];
        if(!ui->lineEdit->text().isEmpty())
        {
            /*Есть данные в поле*/
            filename+="_№"+ui->lineEdit->text();
        }
        filename+="_"+formattedTime;
        filename.replace(":",".");

        /*ВСе из листа в QString*/
        /*перебрать все строки и записать*/
        int count = ui->listWidget->count();
        for(int index = 0; index < count; ++index)
        {
            QListWidgetItem * item = ui->listWidget->item(index);
            // A wild item has appeared
           // stream << QObject::trUtf8( item->text() );
            data+= item->text();
            data+="<br>";
        }

        QString html =
        "<div align=right>"+ formattedTime + "</div>"

        "<h1 align=center>Отчет</h1><br>"
        "<p  style=\"font-size: 12px\" align=justify>" + data + "</p>";

        QTextDocument document;
        document.setHtml(html);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName("./" + filename + ".pdf");
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));

        document.print(&printer);
    }
}


/*по нажатию кнопки идет поиск следующего теста, при отсутствии, ничего не происходит, дойдя до конца идет по кругу*/
void MainWindow::FindAndSelectNextItemInList(QString str)
{
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    QVector <QString> data;
    /*перебрать все строки и записать в файл*/
    int count = ui->listWidget->count();
    for(int index = 0; index < count; ++index)
    {
        QListWidgetItem * item = ui->listWidget->item(index);
        data.push_back(item->text());
    }
    auto currIter = data.begin();

    if (selectedItem) {
        int selectedIndex = ui->listWidget->row(selectedItem);
        // selectedIndex - индекс выделенного элемента
        currIter += selectedIndex;
        // Выделенный элемент последний в списке по совпадению?
        auto iterIsEndOfList = data.lastIndexOf(str);
        if(iterIsEndOfList != -1)
        {
            if (iterIsEndOfList == selectedIndex)
            {
                auto res = std::find(data.begin(), data.end(), str);
                if(res!= data.end())
                {
                    //Строка найдена
                    ui->listWidget->setCurrentRow(data.indexOf(*res));
                }
            }
        }
        else
        {

        }
        auto res = std::find(currIter+1, data.end(), str);
        if(res!= data.end())
        {
            //Строка найдена
            auto dbg = data.indexOf(*res,selectedIndex+1);
            ui->listWidget->setCurrentRow(data.indexOf(*res,selectedIndex+1));
        }

    } else {
        // Ни один элемент не выделен
        auto res = std::find(data.begin(), data.end(), str);
        if(res!= data.end())
        {
            //Строка найдена
            ui->listWidget->setCurrentRow(data.indexOf(*res));
        }

    }

}



void MainWindow::onUserMove(int position)
{
    if (position == ui->listWidget->verticalScrollBar()->maximum()) {
       scroll_helper = true;
    }
    // Если ползунок выше нижней позиции, отключаем "магнит"
    else {
       scroll_helper = false;
    }

}

void MainWindow::onItemAdded()
{
    //added item to list
    if (scroll_helper) {
        ui->listWidget->scrollToBottom();

    }

}


/*Функция выбора активной кнопки*/
void MainWindow::SetActiveButton(int num)
{
    switch (num) {
        case 0:
        ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
        ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->tabWidget->setCurrentIndex(num);//index
        break;
        case 1:
        ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
        ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->tabWidget->setCurrentIndex(num);//index
        break;
        case 2:
        ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
        ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->tabWidget->setCurrentIndex(num);//index
        break;
        case 3:
        ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
        ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->tabWidget->setCurrentIndex(num);//index
        break;
        case 4:
        ui->pushButton_EBMK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_MU1->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_RK->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_UP->setStyleSheet(StyleHelper::getStartButtonsStyleUnSet());
        ui->pushButton_about->setStyleSheet(StyleHelper::getStartButtonsStyleSet());
        ui->tabWidget->setCurrentIndex(num);//index
        break;
        default:break;

    }
}

void MainWindow::SetStyleForTestButtons(QVector<QPushButton *> *vec)
{
    for(auto &i : *vec)
    {
        i->setStyleSheet(StyleHelper::getTestButtonStyle());
    }
}

void MainWindow::SetStyleForStatusButtons(QVector<QPushButton *> *vec)
{
    for(auto &i : *vec)
    {
        i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
    }
}

void MainWindow::SetStyleForChecks(QVector<QCheckBox *> *vec)
{
    for(auto &i : *vec)
    {
        i->setStyleSheet(StyleHelper::getCheckBoxSettings());
        i->setCheckState(Qt::Checked);
    }
}

void MainWindow::AccumulateAndSetAllCheckBoxes()
{
    /*анализ галочек вкладки ЭБМК*/
    auto state = std::count_if(EBMK_tests_checks.begin(),EBMK_tests_checks.end(),[](QCheckBox *i){return i->isChecked();});
    (state == EBMK_tests_checks.count())? ui->checkBox_EBMK_All->setChecked(1): ui->checkBox_EBMK_All->setChecked(0);

    /*анализ галочек вкладки MU1*/
    state = std::count_if(MU1_tests_checks.begin(),MU1_tests_checks.end(),[](QCheckBox *i){return i->isChecked();});
    (state == MU1_tests_checks.count())? ui->checkBox_MU1_All->setChecked(1): ui->checkBox_MU1_All->setChecked(0);

    /*анализ галочек вкладки UP*/
    state = std::count_if(UP_tests_checks.begin(),UP_tests_checks.end(),[](QCheckBox *i){return i->isChecked();});
    (state == UP_tests_checks.count())? ui->checkBox_UP_All->setChecked(1): ui->checkBox_UP_All->setChecked(0);

}

void MainWindow::SetStringInListAsError()
{
    QBrush brush;
    QColor brushColor;
    brushColor.setRgb(255 ,0, 0, 100);
    brush.setColor(brushColor);
    brush.setStyle(Qt::SolidPattern);
    ui->listWidget->item(ui->listWidget->count() - 1)->setBackground(brush);
}

void MainWindow::ClearAllData()
{
    ui->listWidget->clear();
    /*Использование функций из стартовой  инициализации*/
    SetStyleForChecks(&EBMK_tests_checks);
    SetStyleForChecks(&MU1_tests_checks);
    SetStyleForChecks(&UP_tests_checks);
    ui->checkBox_EBMK_All->setChecked(true);
    ui->checkBox_MU1_All->setChecked(true);
    ui->checkBox_UP_All->setChecked(true);

    //сброс всех кнопок в неактивное состояние
    for(auto &i:EBMK_status_buttons)
    {
        i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
    }

    for(auto &i:MU1_status_buttons)
    {
        i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
    }

    for(auto &i:UP_status_buttons)
    {
        i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
    }

}

void MainWindow::SetEnableStatusForAllButtons(bool status)
{
    QString toolTipString = "Для продолжения работы остановите тестирование";

    ui->pushButton_EBMK->setEnabled(status);
    ui->pushButton_MU1->setEnabled(status);
    ui->pushButton_UP->setEnabled(status);
    ui->pushButton_RK->setEnabled(status);
    ui->pushButton_about->setEnabled(status);
    ui->lineEdit->setEnabled(status);
    ui->checkBox_cycle->setEnabled(status);
    ui->pushButton_Clear->setEnabled(status);
    ui->pushButton_Save->setEnabled(status);

    //чекбоксы вкладки ЭБМК
    for(auto &i:EBMK_tests_checks)
    {
        i->setEnabled(status);
    }
    ui->checkBox_EBMK_All->setEnabled(status);

    //чекбоксы вкладки МУ1
    for(auto &i:MU1_tests_checks)
    {
        i->setEnabled(status);
    }
    ui->checkBox_MU1_All->setEnabled(status);

    //чекбоксы вкладки Устр питания
    for(auto &i:UP_tests_checks)
    {
        i->setEnabled(status);
    }
    ui->checkBox_UP_All->setEnabled(status);

    if(!status)
    {
        //выключить активность
       toolTipString = "Для продолжения работы остановите тестирование";

    }
    else
    {
        //включить
        toolTipString = "";

    }

    //тултипы
    ui->pushButton_EBMK->setToolTip(toolTipString);
    ui->pushButton_MU1->setToolTip(toolTipString);
    ui->pushButton_UP->setToolTip(toolTipString);
    ui->pushButton_RK->setEnabled(status);
    ui->pushButton_about->setToolTip(toolTipString);
    ui->lineEdit->setToolTip(toolTipString);
    ui->checkBox_cycle->setToolTip(toolTipString);
    ui->pushButton_Clear->setToolTip(toolTipString);
    ui->pushButton_Save->setToolTip(toolTipString);

    for(auto &i:EBMK_tests_checks)
    {
        i->setToolTip(toolTipString);
    }
    ui->checkBox_EBMK_All->setToolTip(toolTipString);

    for(auto &i:MU1_tests_checks)
    {
        i->setToolTip(toolTipString);
    }
    ui->checkBox_MU1_All->setToolTip(toolTipString);

    for(auto &i:UP_tests_checks)
    {
        i->setToolTip(toolTipString);
    }
    ui->checkBox_UP_All->setToolTip(toolTipString);

}

quint8 MainWindow::GetCurrentTabIndex()
{
    return ui->tabWidget->currentIndex();
}




void MainWindow::on_pushButton_EBMK_clicked()
{
    SetActiveButton(0);
    /*изменение размера и видимость кнопок*/
    ui->label_8->setVisible(true);
    ui->groupBox->setVisible(true);
    ui->listWidget->setVisible(true);

    /*Если текущий индекс не соответствует сохраненному*/
    if(currentTab != GetCurrentTabIndex())
    {
        currentTab = GetCurrentTabIndex();
        ClearAllData();
    }

    /*dbg*/
    log.write("11");
    ui->listWidget->addItem("err");
   // ui->listWidget->item(ui->listWidget->count() - 1)->setBackgroundColor(Qt::red);
    SetStringInListAsError();




}


void MainWindow::on_pushButton_MU1_clicked()
{
    SetActiveButton(1);
    /*изменение размера и видимость кнопок*/
    ui->label_8->setVisible(true);
    ui->groupBox->setVisible(true);
    ui->listWidget->setVisible(true);

    /*Если текущий индекс не соответствует сохраненному*/
    if(currentTab != GetCurrentTabIndex())
    {
        currentTab = GetCurrentTabIndex();
        ClearAllData();
    }
    ui->listWidget->addItem("tst Проверка шрифта 0x858585 ЙЦУКЕН!!!!!!!!");


}


void MainWindow::on_pushButton_UP_clicked()
{
    SetActiveButton(2);
    /*изменение размера и видимость кнопок*/
    ui->label_8->setVisible(true);
    ui->groupBox->setVisible(true);
    ui->listWidget->setVisible(true);

    /*Если текущий индекс не соответствует сохраненному*/
    if(currentTab != GetCurrentTabIndex())
    {
        currentTab = GetCurrentTabIndex();
        ClearAllData();
    }
    ui->listWidget->addItem("UP");

}


void MainWindow::on_pushButton_RK_clicked()
{
    SetActiveButton(3);
    /*изменение размера и видимость кнопок*/
    ui->label_8->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->listWidget->setVisible(false);

    /*Если текущий индекс не соответствует сохраненному*/
    if(currentTab != GetCurrentTabIndex())
    {
        currentTab = GetCurrentTabIndex();
        ClearAllData();
    }

}


void MainWindow::on_pushButton_about_clicked()
{
    SetActiveButton(4);
    /*изменение размера и видимость кнопок*/
    ui->label_8->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->listWidget->setVisible(false);

    /*Если текущий индекс не соответствует сохраненному*/
    if(currentTab != GetCurrentTabIndex())
    {
        currentTab = GetCurrentTabIndex();
        ClearAllData();
    }

}




void MainWindow::on_checkBox_EBMK_All_clicked()
{
    auto state = ui->checkBox_EBMK_All->isChecked();
    for(auto &i : EBMK_tests_checks)
    {
        i->setChecked(state);
    }
}


void MainWindow::on_checkBox_MU1_All_clicked()
{
    auto state = ui->checkBox_MU1_All->isChecked();
    for(auto &i : MU1_tests_checks)
    {
        i->setChecked(state);
    }
}


void MainWindow::on_checkBox_UP_All_clicked()
{
    auto state = ui->checkBox_UP_All->isChecked();
    for(auto &i : UP_tests_checks)
    {
        i->setChecked(state);
    }
}

/*Отсюда и ниже идут слоты анализа чекбоксов для выставления галочек "все"*/
/*====================НАЧАЛО====================*/
void MainWindow::on_checkBox_EBMK_MIEA_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_ASV_SIN_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_ASV_SIN_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_ASV_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_15V_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_PRIBL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_PRIBL_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_ASP_SKVT_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_ASP_SKVT_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_DAVL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_RKP_0_28_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_EBMK_RKP_0_28_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_MIEA_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASV_SIN_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASV_SIN_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASV_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_PRIBL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_PRIBL_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASP_SKVT_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASP_SKVT_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASP_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_ASP_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_DAVL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_0_28_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_0_28_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_28_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_28_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKV_TTL_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_TTL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_RKP_TTL_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_OUT_PWM_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_OZU_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_PZU_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_MU1_REGISTRATOR_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_15V_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_KRKV_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_KRKV_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_OUT_PWM_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_RKP_TTL_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_RKP_TTL_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_ASP_Kom_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_ASP_Ind_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}


void MainWindow::on_checkBox_UP_OUT_PWM_EXO_clicked()
{
    AccumulateAndSetAllCheckBoxes();
}
/*====================КОНЕЦ====================*/



void MainWindow::on_pushButton_Clear_clicked()
{
    ClearAllData();

}


/*Сохранить*/
void MainWindow::on_pushButton_Save_clicked()
{
    QString strFilter="*.log";
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    QString filename;
    filename = Module_names_eng_short[GetCurrentTabIndex()];
    if(!ui->lineEdit->text().isEmpty())
    {
        /*Есть данные в поле*/
        filename+="_№"+ui->lineEdit->text();
    }
    filename+="_"+formattedTime;
    filename.replace(":",".");
    QString str = QFileDialog::getSaveFileName(0,
                                    "Сохранить отчет о работе программы",
                                    ":\\"+filename,
                                    "*.log ;; *.txt",
                                    &strFilter
                                    );
    if(str.isEmpty())
    {
        /*имя не указано*/
        return;
    }
    //открыть файл на запись
       QFile out( str );
       if( out.open( QIODevice::WriteOnly ) )
       {
           QTextStream stream( &out );

    /*перебрать все строки и записать в файл*/
    int count = ui->listWidget->count();
    for(int index = 0; index < count; ++index)
    {
        QListWidgetItem * item = ui->listWidget->item(index);
        // A wild item has appeared
       // stream << QObject::trUtf8( item->text() );
        stream << item->text() << "\n";
    }

    out.close();
    }
}


/*КНОПКА СТАРТ*/
void MainWindow::on_pushButton_Start_Stop_clicked()
{
    /*При разработке многопоточной программы в qt рассматривалось 2 варианта архитектуры.
     * 1. Через QtConcurrent, 2. Через переопределение QThread + слоты-сигналы для вывода информации на основную форму
     Во избежании нарушений принципов SOLID, предпочтение было отдану второму варианту.
        Для каждого теста будет разработан собственный namespace для удобства работы и понятности в названиях функций*/

    QString buf;
    /*Поток не запущен, старт*/
    if(!is_thread_running)
    {
        is_thread_running = true;
        emit SetStop(false);
        //Очистить все
        ui->listWidget->clear();
        //сброс всех кнопок в неактивное состояние
        for(auto &i:EBMK_status_buttons) i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
        for(auto &i:MU1_status_buttons) i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());
        for(auto &i:UP_status_buttons) i->setStyleSheet(StyleHelper::getStatusButtonStyleClear());

        //задать имя кнопке
        ui->pushButton_Start_Stop->setText("Стоп");
        //заблокировать все кнопки и выписать подсказки
        SetEnableStatusForAllButtons(false);
        //вывод времени, названия модуля, номера изделия, если введено
        buf = "Тестируемый модуль: " + Module_names_rus_full[GetCurrentTabIndex()];
        ui->listWidget->addItem(buf);
        /*добавить данные со стартовой формы, отк, оператор и тп*/
        if(!_operator.isEmpty())
        {
            buf = "Оператор: " + _operator;
            ui->listWidget->addItem(buf);
        }
        /*отк*/
        if(!_otk.isEmpty())
        {
            buf = "Представитель ОТК: " + _otk;
            ui->listWidget->addItem(buf);
        }
        /*ВП МО*/
        if(!_vpmo.isEmpty())
        {
            buf = "Представитель ВП МО: " + _vpmo;
            ui->listWidget->addItem(buf);
        }
        /*температура*/
        if(!_temper.isEmpty())
        {
            buf = "Температура: С " + _temper;
            ui->listWidget->addItem(buf);
        }
        if(!ui->lineEdit->text().isEmpty())
        {
            //вывод номера изделия
            buf = "Номер изделия: №" + ui->lineEdit->text();
            ui->listWidget->addItem(buf);
        }
        Tests->SetModuleType(GetCurrentTabIndex());
        Tests->start();
    }
    else
    {
        is_thread_running = false;
        //Поток запущен, стоп
        emit SetStop(true);
        Tests->wait();//ждать остановки
        //задать имя кнопке
        ui->pushButton_Start_Stop->setText("Старт");
        //разблокировать все кнопки и удалить подсказки
        SetEnableStatusForAllButtons(true);


    }


}



/*Обработка нажатия кнопок теста, переход к результатам выбранного теста*/
//==================НАЧАЛО========================

void MainWindow::on_pushButton_EBMK_MIEA_clicked()
{
    emit FindInList(Test_MIEA_name);
}


void MainWindow::on_pushButton_EBMK_ASV_SIN_Kom_clicked()
{
    emit FindInList(Test_ASV_SIN_Kom_name);
}


void MainWindow::on_pushButton_EBMK_ASV_SIN_Ind_clicked()
{
    emit FindInList(Test_ASV_SIN_Ind_name);
}


void MainWindow::on_pushButton_EBMK_ASV_Kom_clicked()
{
    emit FindInList(Test_ASV_Kom_name);
}


void MainWindow::on_pushButton_EBMK_15V_clicked()
{
    emit FindInList(Test_15V_name);
}


void MainWindow::on_pushButton_EBMK_PRIBL_Kom_clicked()
{
    emit FindInList(Test_PRIBL_Kom_name);
}


void MainWindow::on_pushButton_EBMK_PRIBL_Ind_clicked()
{
    emit FindInList(Test_PRIBL_Ind_name);
}


void MainWindow::on_pushButton_EBMK_ASP_SKVT_Kom_clicked()
{
    emit FindInList(Test_ASP_SKVT_Kom_name);
}


void MainWindow::on_pushButton_EBMK_ASP_SKVT_Ind_clicked()
{
    emit FindInList(Test_ASP_SKVT_Kom_name);
}


void MainWindow::on_pushButton_EBMK_DAVL_Kom_clicked()
{
    emit FindInList(Test_DAVL_name);
}


void MainWindow::on_pushButton_EBMK_RKP_0_28_Kom_clicked()
{
    emit FindInList(Test_RKP_0_28_Kom_name);
}


void MainWindow::on_pushButton_EBMK_RKP_0_28_Ind_clicked()
{
    emit FindInList(Test_RKP_0_28_Ind_name);
}


void MainWindow::on_pushButton_MU1_MIEA_clicked()
{
    emit FindInList(Test_MIEA_name);
}


void MainWindow::on_pushButton_MU1_ASV_SIN_Kom_clicked()
{
    emit FindInList(Test_ASV_SIN_Kom_name);
}

void MainWindow::on_pushButton_MU1_ASV_SIN_Ind_clicked()
{
    emit FindInList(Test_ASV_SIN_Ind_name);
}


void MainWindow::on_pushButton_MU1_ASV_Kom_clicked()
{
    emit FindInList(Test_ASV_Kom_name);
}


void MainWindow::on_pushButton_MU1_PRIBL_Kom_clicked()
{
    emit FindInList(Test_PRIBL_Kom_name);
}


void MainWindow::on_pushButton_MU1_PRIBL_Ind_clicked()
{
    emit FindInList(Test_PRIBL_Ind_name);
}


void MainWindow::on_pushButton_MU1_ASP_SKVT_Kom_clicked()
{
    emit FindInList(Test_ASP_SKVT_Kom_name);
}


void MainWindow::on_pushButton_MU1_ASP_SKVT_Ind_clicked()
{
    emit FindInList(Test_ASP_SKVT_Ind_name);
}


void MainWindow::on_pushButton_MU1_ASP_Kom_clicked()
{
    emit FindInList(Test_ASP_Kom_name);
}


void MainWindow::on_pushButton_MU1_ASP_Ind_clicked()
{
    emit FindInList(Test_ASP_Ind_name);
}


void MainWindow::on_pushButton_MU1_DAVL_Kom_clicked()
{
    emit FindInList(Test_DAVL_name);
}


void MainWindow::on_pushButton_MU1_RKP_0_28_Kom_clicked()
{
    emit FindInList(Test_RKP_0_28_Kom_name);
}


void MainWindow::on_pushButton_MU1_RKP_0_28_Ind_clicked()
{
    emit FindInList(Test_RKP_0_28_Ind_name);
}


void MainWindow::on_pushButton_MU1_RKP_28_Kom_clicked()
{
    emit FindInList(Test_RKP_28_Kom_name);
}


void MainWindow::on_pushButton_MU1_RKP_28_Ind_clicked()
{
    emit FindInList(Test_RKP_28_Ind_name);
}


void MainWindow::on_pushButton_MU1_RKV_TTL_Ind_clicked()
{
    emit FindInList(Test_RKV_TTL_Ind_name);
}


void MainWindow::on_pushButton_MU1_RKP_TTL_Kom_clicked()
{
    emit FindInList(Test_RKP_TTL_Kom_name);
}


void MainWindow::on_pushButton_MU1_RKP_TTL_Ind_clicked()
{
    emit FindInList(Test_RKP_TTL_Ind_name);
}


void MainWindow::on_pushButton_MU1_OUT_PWM_Kom_clicked()
{
    emit FindInList(Test_OUT_PWM_Kom_name);
}


void MainWindow::on_pushButton_MU1_OZU_clicked()
{
    emit FindInList(Test_OZU_name);
}


void MainWindow::on_pushButton_MU1_PZU_clicked()
{
    emit FindInList(Test_PZU_name);
}


void MainWindow::on_pushButton_MU1_REGISTRATOR_clicked()
{
    emit FindInList(Test_REGISTRATOR_name);
}


void MainWindow::on_pushButton_UP_15V_clicked()
{
    emit FindInList(Test_15V_name);
}


void MainWindow::on_pushButton_UP_KRKV_Kom_clicked()
{
    emit FindInList(Test_KRKV_Kom_name);
}


void MainWindow::on_pushButton_UP_KRKV_Ind_clicked()
{
    emit FindInList(Test_KRKV_Ind_name);
}


void MainWindow::on_pushButton_UP_OUT_PWM_Kom_clicked()
{
    emit FindInList(Test_OUT_PWM_Kom_name);
}


void MainWindow::on_pushButton_UP_RKP_TTL_Kom_clicked()
{
    emit FindInList(Test_RKP_TTL_Kom_name);
}


void MainWindow::on_pushButton_UP_RKP_TTL_Ind_clicked()
{
    emit FindInList(Test_RKP_TTL_Ind_name);
}


void MainWindow::on_pushButton_UP_ASP_Kom_clicked()
{
    emit FindInList(Test_ASP_Kom_name);
}


void MainWindow::on_pushButton_UP_ASP_Ind_clicked()
{
    emit FindInList(Test_ASP_Ind_name);
}


void MainWindow::on_pushButton_UP_OUT_PWM_EXO_clicked()
{
    emit FindInList(Test_OUT_PWM_EXO_name);
}

