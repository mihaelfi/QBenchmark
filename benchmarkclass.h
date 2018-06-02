#ifndef BENCHMARKCLASS_H
#define BENCHMARKCLASS_H

#include <QObject>
#include <QElapsedTimer>
#include <QEventLoop>


#define NUMBER_OF_SERIALIZED_ITEMS (200)

class BenchmarkClass : public QObject
{
    Q_OBJECT
public:
    explicit BenchmarkClass(QObject *parent = nullptr);



private:
    void benchmarkOne (int number_of_elements_to_serialize);
    void benchmarkProcessEventsBusyLoop();
    void benchmarkEventLoopBusyLoop();

    void benchmarkFour();

    QElapsedTimer _mTimer;
    bool gotIntteruptSignal = false;
    QEventLoop loop;


signals:

public slots:
    void benchmarkSerialization(int number_of_elements_to_serialize);
    void startBenchmarkProcessEventsBusyLoop();
    void startBenchmarkEventLoopBusyLoop();
    void startBenchmarkFour();
    void intteruptLoop();
};

#endif // BENCHMARKCLASS_H
