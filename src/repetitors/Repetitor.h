#ifndef REPETITORPLATFORM_REPETITOR_H
#define REPETITORPLATFORM_REPETITOR_H


#include <QString>
#include <QMap>
#include <QDate>

class Repetitor {
protected:
    // Основные свойства репетитора
    QString name;
    QString subject;
    QDate availableDate;

    // Дополнительные данные, например, события
    QMap<QDate, QString> events;

public:
    // Конструкторы
    Repetitor() = default;
    Repetitor(const QString &name, const QString &subject, const QDate &date)
            : name(name), subject(subject), availableDate(date) {}

    // Геттеры и сеттеры
    QString getName() const { return name; }
    void setName(const QString &name) { this->name = name; }

    QString getSubject() const { return subject; }
    void setSubject(const QString &subject) { this->subject = subject; }

    QDate getAvailableDate() const { return availableDate; }
    void setAvailableDate(const QDate &date) { this->availableDate = date; }

    // Методы работы с событиями
    void addEvent(const QDate &date, const QString &event) {
        events[date] = event;
    }

    QString getEvent(const QDate &date) const {
        return events.contains(date) ? events.value(date) : QString();
    }

    QMap<QDate, QString> getAllEvents() const {
        return events;
    }
};

#endif
