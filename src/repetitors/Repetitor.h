#ifndef REPETITORPLATFORM_REPETITOR_H
#define REPETITORPLATFORM_REPETITOR_H

#include <QString>
#include <QMap>
#include <QDate>

class Repetitor {
protected:
    // Имя репетитора
    QString subject;           // Предмет
    QString name;
public:
    // Конструкторы
    Repetitor() = default;
    Repetitor(const QString &name, const QString &subject)
            : name(name), subject(subject) {}

    // Методы для работы с именем
    QString getName() const { return name; }
    void setName(const QString &name) { this->name = name; }

    // Методы для работы с предметом
    QString getSubject() const { return subject; }
    void setSubject(const QString &subject) { this->subject = subject; }
};

#endif // REPETITORPLATFORM_REPETITOR_H
