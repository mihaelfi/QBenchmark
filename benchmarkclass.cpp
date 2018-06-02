#include "benchmarkclass.h"
#include <QDebug>
#include <QDataStream>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QByteArray>
#include <QCoreApplication>
#include <QTimer>
#include <QHash>

#include "common_defs.h"


BenchmarkClass::BenchmarkClass(QObject *parent) : QObject(parent)
{
    _mTimer = QElapsedTimer();

}

void BenchmarkClass::benchmarkOne(int number_of_elements_to_serialize)
{
    // test for 20 elements

    QList<QString> myList;
    QMap<QString,QString> myMap;

    for (int i = 0 ; i < number_of_elements_to_serialize  ; i++)
    {
        QString key = QString("My Key #%1").arg(i);

        myList.append(key);
        myList.append("My Value");
        myMap.insert(key,"My Value");
    }

    QByteArray listByteArray;
    QByteArray mapByteArray;

    QDataStream myListStream(&listByteArray,QIODevice::WriteOnly);
    QDataStream myMapStream(&mapByteArray,QIODevice::WriteOnly);


    _mTimer.start();
    myListStream << myList;

    auto listSerializationElapsedTime = _mTimer.nsecsElapsed();
    auto sizeOfListByteArray = listByteArray.size();

    _mTimer.restart();

    myMapStream << myMap;

    auto mapSerializationElapsedTime = _mTimer.nsecsElapsed();
    auto sizeOfMapByteArray = mapByteArray.size();



    qDebug() << tr("For %1 elements, Seralization of List took %2 nano seconds, and of Map took %3 nano seconds."
                "Size of Serialized bytearray of list is: %4 and size of serialized map is: %5")
                .arg(number_of_elements_to_serialize).arg(listSerializationElapsedTime).arg(mapSerializationElapsedTime)
                .arg(sizeOfListByteArray).arg(sizeOfMapByteArray);



}

void BenchmarkClass::benchmarkProcessEventsBusyLoop()
{

    //process events busy loop:
    qDebug() << tr("%1::%2 Entering 'process events' busy loop...").arg(this->metaObject()->className()).arg(__func__);

    QTimer::singleShot(15000, this, SLOT(intteruptLoop()));

    while (false == this->gotIntteruptSignal)
    {
        QCoreApplication::processEvents();
    }

    qDebug() << tr(" %1::%2 Got intterupt signal From Gui... Quiting busy loop, and resseting interrupt variable to false")
                .arg(this->metaObject()->className()).arg(__func__);

    this->gotIntteruptSignal = false;

}

void BenchmarkClass::benchmarkEventLoopBusyLoop()
{
    qDebug() << tr("%1::%2 Entering 'event loop' busy loop...").arg(this->metaObject()->className()).arg(__func__);

    QTimer::singleShot(15000, this, SLOT(intteruptLoop()));

    this->loop.exec();
     qDebug() <<  tr("%1::%2 Got intterupt signal ...").arg(this->metaObject()->className()).arg(__func__);

}

void BenchmarkClass::benchmarkFour()
{
    MyErrorStruct myErrorStruct;

    myErrorStruct.errorCode = 1984;
    myErrorStruct.errorString = "1984 was written by George Orwell.";

    MyStruct myStruct;

    myStruct.intNumber = 7;
    myStruct.doubleNumber = 8.2;
    myStruct.qString= "This is a string in a struct";
    myStruct.myError = myErrorStruct;
    myStruct.username = "Joseph";
    myStruct.password = "123456";
    myStruct.fullname = "Joseph Smith Father of scientology!";
    myStruct.longJsonString = "NOT REEALLY JSON... JUST LONG STRING...";


    QMap<MapKeys,QVariant> myMap;

    myMap.insert(ERROR_ERROR_CODE,QVariant(myErrorStruct.errorCode));
    myMap.insert(ERROR_ERROR_STRING,QVariant(myErrorStruct.errorString));

    myMap.insert(DATA_INT_NUM,QVariant(myStruct.intNumber));
    myMap.insert(DATA_DOUBLE_NUM,QVariant(myStruct.doubleNumber));
    myMap.insert(DATA_QSTRING,QVariant(myStruct.qString));
    myMap.insert(DATA_USERNAME,QVariant(myStruct.username));
    myMap.insert(DATA_PASSWORD,QVariant(myStruct.password));
    myMap.insert(DATA_FULLNAME,QVariant(myStruct.fullname));
    myMap.insert(DATA_LONG_JSON_STRING,QVariant(myStruct.longJsonString));


    QHash<MapKeys,QVariant> myHash;

    myHash.insert(ERROR_ERROR_CODE,QVariant(myErrorStruct.errorCode));
    myHash.insert(ERROR_ERROR_STRING,QVariant(myErrorStruct.errorString));

    myHash.insert(DATA_INT_NUM,QVariant(myStruct.intNumber));
    myHash.insert(DATA_DOUBLE_NUM,QVariant(myStruct.doubleNumber));
    myHash.insert(DATA_QSTRING,QVariant(myStruct.qString));
    myHash.insert(DATA_USERNAME,QVariant(myStruct.username));
    myHash.insert(DATA_PASSWORD,QVariant(myStruct.password));
    myHash.insert(DATA_FULLNAME,QVariant(myStruct.fullname));
    myHash.insert(DATA_LONG_JSON_STRING,QVariant(myStruct.longJsonString));



    QByteArray structByteArray;
    QByteArray variantMapByteArray;
    QByteArray variantHashMapByteArray;


    QDataStream myStructStream(&structByteArray,QIODevice::WriteOnly);
    QDataStream myMapStream(&variantMapByteArray,QIODevice::WriteOnly);
    QDataStream myHashStream(&variantHashMapByteArray,QIODevice::WriteOnly);


    _mTimer.start();
    myStructStream << myStruct;

    auto structSerializationTime = _mTimer.nsecsElapsed();
    auto structByteArraySize = structByteArray.size();


    _mTimer.restart();
    myMapStream << myMap;

    auto mapSerializationTime = _mTimer.nsecsElapsed();
    auto maptByteArraySize = variantMapByteArray.size();


    _mTimer.restart();
    myHashStream << myHash;

    auto hashSerializationTime = _mTimer.nsecsElapsed();
    auto hashByteArraySize = variantHashMapByteArray.size();


    QString output = QString("\n Struct Serialization time is: %1 \n"
                             "Map Serailzation time is: %2 \n"
                             "Hash Serialization time is: %3 \n"
                             "\n"
                             "Struct ByteArray Size is: %4 \n"
                             "Map ByteArraySize is: %5 \n"
                             "Hash ByteArray Size is: %6\n")
            .arg(structSerializationTime).arg(mapSerializationTime)
            .arg(hashSerializationTime).arg(structByteArraySize).arg(maptByteArraySize).arg(hashByteArraySize);


    qDebug() << tr("%1::%2, %3").arg(this->metaObject()->className()).arg(__func__).arg(output);



}

void BenchmarkClass::benchmarkSerialization(int number_of_elements_to_serialize)
{
    this->benchmarkOne(number_of_elements_to_serialize);
}

void BenchmarkClass::startBenchmarkProcessEventsBusyLoop()
{
    this->benchmarkProcessEventsBusyLoop();
}

void BenchmarkClass::startBenchmarkEventLoopBusyLoop()
{
    this->benchmarkEventLoopBusyLoop();
}

void BenchmarkClass::startBenchmarkFour()
{
    this->benchmarkFour();
}

void BenchmarkClass::intteruptLoop()
{
    this->gotIntteruptSignal = true;
    this->loop.quit();
}
