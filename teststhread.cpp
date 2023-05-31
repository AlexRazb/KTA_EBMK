#include "teststhread.h"
#include "mainwindow.h"
#include "test_names.h"
#include <QTime>

/*Основной класс-поток для вызова всех тестов*/
/*передаваемые параметры:
 * 1) ид вкладки 0-ЭБМК, 1-МУ1, 2-Устройство питания
   2) Вектор указателей на галочки с текущей вкладки*/
TestsThread::TestsThread(qint8 _moduleType, QCheckBox *_ptrToCycleCheckBox, QVector<QCheckBox*>*_ptrToCheckBoxesFromEBMKTab, QVector<QCheckBox*>*_ptrToCheckBoxesFromMU1Tab, QVector<QCheckBox*>*_ptrToCheckBoxesFromUPTab ): ptrToCheckBoxesFromEBMKTab(_ptrToCheckBoxesFromEBMKTab), ptrToCheckBoxesFromMU1Tab(_ptrToCheckBoxesFromMU1Tab), ptrToCheckBoxesFromUPTab(_ptrToCheckBoxesFromUPTab), moduleType(_moduleType), ptrToCycleCheckBox(_ptrToCycleCheckBox)
{

    /*Заполнить вектор с параметрами, передаваемыми в функцию, после Заполнить вектор вызываемыми функциями для тестирования ЭБМК*/
    /*Ниже идут построчно пары Параметр - Функция*/
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_MIEA);//MIEA
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_ASV_SIN);//АСВ Синус КОМ
    EBMK_Tests_parameters.append(IND);       EBMK_Tests.append(&TestsThread::Test_ASV_SIN);//АСВ Синус Инд
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_ASV);//АСВ КОМ
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_15V);//Питание датчиков +15В
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_PRIBL);//Датчики приближения Ком
    EBMK_Tests_parameters.append(IND);       EBMK_Tests.append(&TestsThread::Test_PRIBL);//Датчики приближения Инд
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_ASP_SKVT);//АСП СКВТ КОМ
    EBMK_Tests_parameters.append(IND);       EBMK_Tests.append(&TestsThread::Test_ASP_SKVT);//АСП СКВТ ИНД
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_DAVL);//Датчик давления
    EBMK_Tests_parameters.append(KOM);       EBMK_Tests.append(&TestsThread::Test_RKP_0_28);//РКП 0-28 Обрыв Ком
    EBMK_Tests_parameters.append(IND);       EBMK_Tests.append(&TestsThread::Test_RKP_0_28);//РКП 0-28 Обрыв Инд

    /*Заполнить вектор вызываемыми функциями для тестирования МУ-1*/
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_MIEA);//MIEA
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_ASV_SIN);//асв синус ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_ASV_SIN);//асв синус инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_ASV);//асв ком
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_PRIBL);//датчики приближения ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_PRIBL);//датчики приближения инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_ASP_SKVT);//асп сквт ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_ASP_SKVT);//асп сквт инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_ASP);//асп ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_ASP);//асп инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_DAVL);//датчик давления ком
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_RKP_0_28);//ркп 0-28 обрыв ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_RKP_0_28);//ркп 0-28 обрыв инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_RKP_28);//ркп 28 обрыв ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_RKP_28);//ркп 28 обрыв инд
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_RKV_TTL);//ркв ттл инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_RKP_TTL);//ркп ттл ком
    MU1_Tests_parameters.append(IND);        MU1_Tests.append(&TestsThread::Test_RKP_TTL);//ркп ттл инд
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_OUT_PWM);//выходные шим ком
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_OZU);//озу ком
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_PZU);//пзу ком
    MU1_Tests_parameters.append(KOM);        MU1_Tests.append(&TestsThread::Test_REGISTRATOR);//регистратор ком

    /*Заполнить вектор вызываемыми функциями для тестирования Устройства питания*/
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_15V);//питание датчиков 15в ком
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_KRKV);//кркв ком
    UP_Tests_parameters.append(IND);        UP_Tests.append(&TestsThread::Test_KRKV);//кркв инд
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_OUT_PWM);//выходные шим ком
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_RKP_TTL);//ркп ттл ком
    UP_Tests_parameters.append(IND);        UP_Tests.append(&TestsThread::Test_RKP_TTL);//ркп ттл инд
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_ASP);//асп ком
    UP_Tests_parameters.append(IND);        UP_Tests.append(&TestsThread::Test_ASP);//асп инд
    UP_Tests_parameters.append(KOM);        UP_Tests.append(&TestsThread::Test_OUT_PWM_EXO);//выходные шим эхо
}

qint8 TestsThread::GetModuleType()
{
    return moduleType;
}

void TestsThread::SetModuleType(qint8 moduletype)
{
    moduleType = moduletype;
}

/*Тут стартует поток*/
void TestsThread::run()
{
    QTime currTime;
    QString timeText;
    QString buf;
    qint8 TestsCount = 0;//Количество тестов в текущем подмодуле
    QVector<QCheckBox*>*ptrToCurrentChecks;//указатель на текущий вектор с галочками
    QVector<int (TestsThread::*)(int)>*Current_Tests;//указатель на текущие тесты
    QVector<int>*Current_Tests_parameters;//указатель на текущие параметры для передачи в функции тестов
    quint16 HI_byte_is_tab_index_LOW_byte_is_test_index;
    int result = 0;//результат тестирования
    int success_counter = 0;//счетчик успешных тестов
    int checkedStatus = 1;

    if(moduleType == 0)//ebmk
    {
        ptrToCurrentChecks = ptrToCheckBoxesFromEBMKTab;
        TestsCount = ptrToCheckBoxesFromEBMKTab->size();
        Current_Tests = &EBMK_Tests;
        Current_Tests_parameters = &EBMK_Tests_parameters;
    }
    else if (moduleType == 1)//mu1
    {
        ptrToCurrentChecks = ptrToCheckBoxesFromMU1Tab;
        TestsCount = ptrToCheckBoxesFromMU1Tab->size();
        Current_Tests = &MU1_Tests;
        Current_Tests_parameters = &MU1_Tests_parameters;
    }
    else if (moduleType == 2)//up
    {
        ptrToCurrentChecks = ptrToCheckBoxesFromUPTab;
        TestsCount = ptrToCheckBoxesFromUPTab->size();
        Current_Tests = &UP_Tests;
        Current_Tests_parameters = &UP_Tests_parameters;
    }


    /*===Запуск циклла тестирования===*/

    /*время начала*/
    currTime = QTime::currentTime();
    timeText = currTime.toString("hh:mm:ss.zzz");
    buf="Время начала тестов: " + timeText;
    emit Print(buf);

    /*пока нажат цикл, тесты выполняются*/
    while(checkedStatus)
    {
        checkedStatus = ptrToCycleCheckBox->isChecked();
        success_counter = 0;//сброс счетчика
        for(qint32 i = 0;i<TestsCount;++i)
        {
            /*Проверить галочку*/
            /*Если нажата*/
            if(ptrToCurrentChecks->at(i)->isChecked())
            {
                /*Заполнить структуру для передачи в сигнал*/
                HI_byte_is_tab_index_LOW_byte_is_test_index = moduleType << 8;
                HI_byte_is_tab_index_LOW_byte_is_test_index |=i;
                /*Установить режим гиф(тест в работе)*/
                emit Load(HI_byte_is_tab_index_LOW_byte_is_test_index);
                //emit Clear(HI_byte_is_tab_index_LOW_byte_is_test_index);//ЗАТЫЧКА
                /*Вызов теста*/
                result =(this->*Current_Tests->at(i))(Current_Tests_parameters->at(i));
                /*анализ результата*/
                if(result == 0)
                {
                    /*успех*/
                    success_counter++;
                    emit Print("Тест пройден успешно");
                    emit Ok(HI_byte_is_tab_index_LOW_byte_is_test_index);
                }
                else if(result == 1)
                {
                    /*отказ*/
                    emit Print("Отказ теста");
                    emit Err(HI_byte_is_tab_index_LOW_byte_is_test_index);

                }
                else if(result == 2)
                {
                    //остановлен пользователем
                    emit Print("Тест прерван");
                    //добавить очистку поля(белый)
                    emit Clear(HI_byte_is_tab_index_LOW_byte_is_test_index);
                    return;
                }
                else
                {
                    //
                }
            }

        }
        /*Проверка на соответствие ТУ*/
        if(success_counter == TestsCount)
        {
            emit Print("Изделие соответствует ТУ");
        }
       // success_counter = 0;
    }//end while

    /*время окончания тестов*/
    currTime = QTime::currentTime();
    timeText = currTime.toString("hh:mm:ss.zzz");
    buf="Время конца тестов: " + timeText;
    emit Print(buf);

    /*pdf*/
    emit Pdf();

 //   exec();
}

/*Остановка потока*/
void TestsThread::stop()
{

}

void TestsThread::SetStop(bool stop_status)
{
    QMutexLocker locker(&mutex);//аналог локгарда
    user_stop = stop_status;

}

bool TestsThread::IsStop()
{
    QMutexLocker locker(&mutex);//аналог локгарда
    return user_stop;
}


/*==========TESTS==========*/
     /*=====BEGIN=====*/
int TestsThread::Test_MIEA(int channel)
{
    if(IsStop()) return 2;//поток остановлен пользователем
    if(channel == KOM)
    {
        emit Print(Test_MIEA_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    /**/
    emit PrintErr("Err!");
    sleep(1);
    return 1;
    return 0;
}

int TestsThread::Test_ASV_SIN(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_ASV_SIN_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_ASV_SIN_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    sleep(1);
    return 0;
}

int TestsThread::Test_ASV(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_ASV_Kom_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_15V(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_15V_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_PRIBL(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_PRIBL_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_PRIBL_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_ASP_SKVT(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_ASP_SKVT_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_ASP_SKVT_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_DAVL(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_DAVL_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_RKP_0_28(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_RKP_0_28_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_RKP_0_28_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
     sleep(1);
    return 0;
}

int TestsThread::Test_ASP(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_ASP_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_ASP_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_RKP_28(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_RKP_28_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_RKP_28_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_RKV_TTL(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_RKV_TTL_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_RKV_TTL_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_RKP_TTL(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_RKP_TTL_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_RKP_TTL_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_OUT_PWM(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_OUT_PWM_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_OUT_PWM_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_OZU(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_OZU_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    /**/
    sleep(1);
    return 0;
}

int TestsThread::Test_PZU(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_PZU_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    sleep(1);
    /**/
    return 0;
}

int TestsThread::Test_REGISTRATOR(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_REGISTRATOR_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    sleep(1);
    /**/
    return 0;
}

int TestsThread::Test_KRKV(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_KRKV_Kom_name);
    }
    else if(channel == IND)
    {
        emit Print(Test_KRKV_Ind_name);
    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    sleep(1);
    /**/
    return 0;
}

int TestsThread::Test_OUT_PWM_EXO(int channel)
{

    if(channel == KOM)
    {
        emit Print(Test_OUT_PWM_EXO_name);
    }
    else if(channel == IND)
    {

    }
    else
    {
        /*Недопустимый входной параметр*/
    }
    if(IsStop()) return 2;//поток остановлен пользователем
    sleep(1);
    /**/
    return 0;
}

/*=====END TESTS=====*/

