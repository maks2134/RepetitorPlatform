#ifndef CALENDARERROR_H
#define CALENDARERROR_H

#include "ErrorBase.h"
#include <QFile>
#include <QTextStream>
#include <QDate>


class CalendarError : public ErrorBase {
public:
    explicit CalendarError(const QString &message, const QString &context = QString());
    ~CalendarError() override = default;

    void showError() const override;  // Реализация отображения ошибки
    void logError(const QString &logFilePath) const; // Логирование ошибки в файл

    // Предустановленные ошибки
    static CalendarError loadError();
    static CalendarError saveError();
    static CalendarError eventNotFound(const QDate &date);
    static CalendarError invalidEvent(const QString &event);
};

#endif // CALENDARERROR_H
