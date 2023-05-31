#ifndef TESTSTHREAD_H
#define TESTSTHREAD_H
#include <QVector>
#include <QCheckBox>
#include <QThread>
#include <QObject>
#include <QMutex>

#define EBMK 0
#define MU1 1
#define UP 2



class TestsThread: public QThread
{
    Q_OBJECT

public:
    TestsThread(qint8 _moduleType, QCheckBox *_ptrToCycleCheckBox, QVector<QCheckBox*>*_ptrToCheckBoxesFromEBMKTab, QVector<QCheckBox*>*_ptrToCheckBoxesFromMU1Tab, QVector<QCheckBox*>*_ptrToCheckBoxesFromUPTab );
    qint8 GetModuleType();
    void SetModuleType(qint8 moduletype);

signals:
    /*Сигналы для вывода данных на форму*/

    /*Тест успешно завершен*/
    void Ok(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);
    /*Ошибка теста*/
    void Err(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);
    /*Тест прерван пользователем*/
    void Clear(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);
    /*Тест в процессе выполнения*/
    void Load(quint16 HI_byte_is_tab_index_LOW_byte_is_test_index);

    /*Вывод сообщения в листбокс*/
    void Print(QString str);
    /*Вывод сообщения в листбокс с ошибкой*/
    void PrintErr(QString str);

    /*Печать pdf*/
    void Pdf();

protected:
    void run() override;
    void stop();

public slots:
    /*установка статуса*/
    void SetStop(bool stop_status);
private:

    /*для корректной установки сигнала обработки*/
    QMutex mutex;
    bool user_stop;
    /*возвращает сигнал признака остановки программы*/
    bool IsStop();

    /*Контейнер с указателями на чекбоксы вкладки ЭБМК*/
    QVector<QCheckBox*> *ptrToCheckBoxesFromEBMKTab;
    /*Контейнер с указателями на чекбоксы вкладки MU1*/
    QVector<QCheckBox*> *ptrToCheckBoxesFromMU1Tab;
    /*Контейнер с указателями на чекбоксы вкладки UP*/
    QVector<QCheckBox*> *ptrToCheckBoxesFromUPTab;
    /*Тип проверки*/
    qint8 moduleType;

    /*указатель на чекбокс цикла*/
    QCheckBox  *ptrToCycleCheckBox = nullptr;

    int Test_MIEA(int channel);//Привода
    int Test_ASV_SIN(int channel);//синус асв
    int Test_ASV(int channel);//асв
    int Test_15V(int channel);//датчик 15Вольт
    int Test_PRIBL(int channel);//датчик приближения
    int Test_ASP_SKVT(int channel);//датчик асп сквт
    int Test_DAVL(int channel);//датчик давления
    int Test_RKP_0_28(int channel);//ркп 0-28 обрыв
    int Test_ASP(int channel);//датчик асп
    int Test_RKP_28(int channel);//ркп +28 обрыв
    int Test_RKV_TTL(int channel);//ркв ТТЛ
    int Test_RKP_TTL(int channel);//ркп ТТЛ
    int Test_OUT_PWM(int channel);//выходные шим
    int Test_OZU(int channel);//озу
    int Test_PZU(int channel);//пзу
    int Test_REGISTRATOR(int channel);//регистратор
    int Test_KRKV(int channel);//КРКВ
    int Test_OUT_PWM_EXO(int channel);//выходные шим эхо

    /*Вектор указателей на функции для тестирования ЭБМК*/
    QVector<int (TestsThread::*)(int)>EBMK_Tests;

    /*Вектор указателей на функции для тестирования MU1*/
    QVector<int (TestsThread::*)(int)>MU1_Tests;

    /*Вектор указателей на функции для тестирования Устройства питания*/
    QVector<int (TestsThread::*)(int)>UP_Tests;

    /*Вектор с параметрами для передачи в функции. Передача идет строго 1 к 1 [0] [0] и тп*/
    QVector<int>EBMK_Tests_parameters;
    QVector<int>MU1_Tests_parameters;
    QVector<int>UP_Tests_parameters;
};

#endif // TESTSTHREAD_H
