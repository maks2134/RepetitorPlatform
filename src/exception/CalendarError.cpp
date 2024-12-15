#include "CalendarError.h"
#include <QMessageBox>
#include <QDebug>

CalendarError::CalendarError(const QString &message, const QString &context)
        : ErrorBase(message, context) {}

// Отображение ошибки на русском языке
void CalendarError::showError() const {
    QString fullMessage = "Ошибка календаря: " + message;
    if (!context.isEmpty()) {
        fullMessage += "\nКонтекст: " + context;
    }
    QMessageBox::warning(nullptr, "Ошибка календаря", fullMessage);
}

// Логирование ошибки в файл
void CalendarError::logError(const QString &logFilePath) const {
    QFile logFile(logFilePath);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << "Ошибка календаря: " << message << "\n";
        if (!context.isEmpty()) {
            out << "Контекст: " << context << "\n";
        }
        out << "--------------------------\n";
        logFile.close();
    } else {
        qDebug() << "Не удалось открыть файл журнала: " << logFilePath;
    }
}

// Предустановленные ошибки
CalendarError CalendarError::loadError() {
    return CalendarError("Не удалось загрузить данные календаря.", "Проверьте файл и доступ к нему.");
}

CalendarError CalendarError::saveError() {
    return CalendarError("Не удалось сохранить данные календаря.", "Проверьте файл и доступ к нему.");
}

CalendarError CalendarError::eventNotFound(const QDate &date) {
    return CalendarError("Событие на выбранную дату отсутствует.", "Дата: " + date.toString("yyyy-MM-dd"));
}

CalendarError CalendarError::invalidEvent(const QString &event) {
    return CalendarError("Недопустимое событие.", "Событие: " + event);
}
