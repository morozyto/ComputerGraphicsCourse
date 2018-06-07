//
// Created by Tony Morozov on 22.05.2018.
//


///  Колиство кадров, по которым усредняем значение
#define COUNT_OF_FRAMES_TO_AVERAGE 200

#include <sys/resource.h>
#include <sys/times.h>

double sumOfTimes = 0;
double myTimes[COUNT_OF_FRAMES_TO_AVERAGE];
bool isFull = false;
int MyIndex = 0;
double time0;


/// Вызывать этот метод перед отрисовкой
void setTimer() {
    struct rusage rusage;
    if ( getrusage( RUSAGE_SELF, &rusage ) != -1 )
        time0 = (double)rusage.ru_utime.tv_sec + (double)rusage.ru_utime.tv_usec / 1000000.0;
}

/// Вызывать этот метод после отрисовки
void addRecord() {
    struct rusage rusage;
    double time1;
    if ( getrusage( RUSAGE_SELF, &rusage ) != -1 )
        time1 = (double)rusage.ru_utime.tv_sec + (double)rusage.ru_utime.tv_usec / 1000000.0;

    double time = time1 - time0;

    if (isFull) {
        sumOfTimes -= myTimes[MyIndex];
        sumOfTimes += time;
        myTimes[MyIndex] = time;

        MyIndex = (MyIndex + 1) % COUNT_OF_FRAMES_TO_AVERAGE;

    } else {
        myTimes[MyIndex++] = time;
        sumOfTimes += time;
        if (MyIndex == COUNT_OF_FRAMES_TO_AVERAGE) {
            isFull = true;
            MyIndex = 0;
        }
    }

}


double getAverageFPS() {
    if (isFull) {
        return (double)COUNT_OF_FRAMES_TO_AVERAGE / sumOfTimes;
    } else {
        return (double)MyIndex / sumOfTimes;
    }
}

double getAverageSPF() {
    return 1 / getAverageFPS();
}
