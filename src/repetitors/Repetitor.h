#ifndef REPETITORPLATFORM_REPETITOR_H
#define REPETITORPLATFORM_REPETITOR_H

#include <QString>
#include <QMap>
#include <QDate>

class Repetitor {
protected:
    // Имя репетитора
    QString subject;           // Предмет
// Путь к файлу с тестами
    QMap<QDate, QString> events; // События, связанные с репетитором

public:
    // Конструкторы
    Repetitor() = default;
    Repetitor(const QString &name, const QString &subject, const QString &testFilePath)
            : name(name), subject(subject),  testFilePath(testFilePath) {}

    // Методы для работы с именем
    QString getName() const { return name; }
    void setName(const QString &name) { this->name = name; }

    // Методы для работы с предметом
    QString getSubject() const { return subject; }
    void setSubject(const QString &subject) { this->subject = subject; }



    // Методы для работы с тестами
    QString getTestFilePath() const { return testFilePath; }
    void setTestFilePath(const QString &filePath) { this->testFilePath = filePath; }

    // Методы работы с событиями
    void addEvent(const QDate &date, const QString &event) {
        events[date] = event;
    }

    QString getEvent(const QDate &date) const {
        return events.contains(date) ? events.value(date) : QString();
    }

    bool isAvailableOnDate(const QDate &date) const {
        return events.contains(date);
    }

    QMap<QDate, QString> getAllEvents() const {
        return events;
    }

    // Удобный метод для описания репетитора (например, для UI)
    QString toString() const {
        return QString("%1 (%2)").arg(name, subject);
    }

//    QDate availableDate;       // Дата доступности
    QString testFilePath;
    QString name;
};

#endif // REPETITORPLATFORM_REPETITOR_H
