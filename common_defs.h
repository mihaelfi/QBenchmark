#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include <QString>
#include <QByteArray>
#include <QDataStream>

enum MapKeys
{
    ERROR_ERROR_CODE,
    ERROR_ERROR_STRING,

    DATA_INT_NUM,
    DATA_DOUBLE_NUM,
    DATA_QSTRING,
    DATA_USERNAME,
    DATA_PASSWORD,
    DATA_FULLNAME,
    DATA_LONG_JSON_STRING
};

typedef struct _myErrorStruct
{
    quint16 errorCode;
    QString errorString;

    _myErrorStruct()
    {
        Init();
    }

    void Init()
    {
        errorCode = 0;
        errorString.clear();
    }

    friend QDataStream& operator <<(QDataStream& outputStream, _myErrorStruct& sourceData)
    {
        outputStream << sourceData.errorCode
                        << sourceData.errorString;

        return outputStream;

    }

    friend QDataStream& operator >>(QDataStream& inputStream, _myErrorStruct& destData)
    {
        inputStream    >> destData.errorCode
                       >> destData.errorString;

        return inputStream;
    }



}MyErrorStruct;

Q_DECLARE_METATYPE(MyErrorStruct);

typedef struct _myStruct
{
    int     intNumber;
    double  doubleNumber;
    QString qString;
    MyErrorStruct myError;

    QString username;
    QString password;
    QString fullname;
    QString longJsonString;

    _myStruct()
    {
        Init();
    }

    void Init()
    {
        intNumber = 0;
        doubleNumber = 0;
        qString.clear();
        myError.Init();
        username.clear();
        password.clear();
        fullname.clear();
        longJsonString.clear();
    }


    friend QDataStream& operator <<(QDataStream& outputStream, _myStruct& sourceData)
    {
        outputStream << sourceData.intNumber
                        << sourceData.doubleNumber
                        << sourceData.qString
                        << sourceData.myError
                        << sourceData.username
                        << sourceData.password
                        << sourceData.fullname
                        << sourceData.longJsonString;

        return outputStream;

    }

    friend QDataStream& operator >>(QDataStream& inputStream, _myStruct& destData)
    {
        inputStream  << destData.intNumber
                        << destData.doubleNumber
                        << destData.qString
                        << destData.myError
                        << destData.username
                        << destData.password
                        << destData.fullname
                        << destData.longJsonString;

        return inputStream;
    }

}MyStruct;

Q_DECLARE_METATYPE(MyStruct);

#endif // COMMON_DEFS_H
