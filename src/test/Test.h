//
// Created by LENOVO on 17.12.2024.
//

#ifndef REPETITORPLATFORM_TEST_H
#define REPETITORPLATFORM_TEST_H


#include "../repetitors/Repetitor.h"

class Test : public Repetitor{
private:
    QDate date;
    QTime time;
    QString testFilePath;
public:

    Test(const QString& nameRep, const QString& subj, const QDate& date, const QTime& time, const QString& testFilePath)
            : Repetitor(nameRep, subj), date(date), time(time), testFilePath(testFilePath) {}

    // Геттер для date
    QDate getDate() const {
        return date;
    }

    // Сеттер для date
    void setDate(const QDate &newDate) {
        date = newDate;
    }

    // Геттер для time
    QTime getTime() const {
        return time;
    }

    // Сеттер для time
    void setTime(const QTime &newTime) {
        time = newTime;
    }

    // Геттер для testFilePath
    QString getTestFilePath() const {
        return testFilePath;
    }

    // Сеттер для testFilePath
    void setTestFilePath(const QString &newFilePath) {
        testFilePath = newFilePath;
    }
};


#endif //REPETITORPLATFORM_TEST_H
