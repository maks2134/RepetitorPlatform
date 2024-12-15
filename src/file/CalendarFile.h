#ifndef CALENDARFILE_H
#define CALENDARFILE_H

#include "File.h"
#include <QMap>
#include <QDate>

class CalendarFile : public File {
private:
    QMap<QDate, QString> events;

public:
    explicit CalendarFile(const QString &filePath);
    ~CalendarFile() override = default;

    const QMap<QDate, QString> &getEvents() const;

    bool load() override;
    bool save() override;

    void addEvent(const QDate &date, const QString &event);
};

#endif // CALENDARFILE_H
