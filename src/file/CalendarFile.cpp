#include "CalendarFile.h"
#include <QTextStream>

CalendarFile::CalendarFile(const QString &filePath) : File(filePath) {}

const QMap<QDate, QString> &CalendarFile::getEvents() const {
    return events;
}

bool CalendarFile::load() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    events.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(": ");
        if (parts.size() == 2) {
            QDate date = QDate::fromString(parts[0], "yyyy-MM-dd");
            if (date.isValid()) {
                events.insert(date, parts[1]);
            } else {
                qDebug() << "Ошибка: Неверный формат даты в строке:" << line;
            }
        }
    }

    file.close();
    return true;
}

bool CalendarFile::save() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    for (auto it = events.begin(); it != events.end(); ++it) {
        out << it.key().toString("yyyy-MM-dd") << ": " << it.value() << "\n";
    }

    file.close();
    return true;
}

void CalendarFile::addEvent(const QDate &date, const QString &event) {
    events.insert(date, event);
}
