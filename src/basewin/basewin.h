#ifndef REPETITORPLATFORM_BASEWIN_H
#define REPETITORPLATFORM_BASEWIN_H


#include <QWidget>
#include <QMap>
#include <QDate>
#include <QString>
#include <QFile>
#include "../repetitors/Repetitor.h" // Подключаем класс репетитора

class BaseWin : public QWidget, public Repetitor { // Базовый класс, наследуемый от QWidget
Q_OBJECT

protected: // Общая логика доступна наследникам
    QMap<QDate, QString> calendarData;

    void saveCalendarDataToFile(const QString &filePath) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (auto it = calendarData.begin(); it != calendarData.end(); ++it) {
                out << it.key().toString("yyyy-MM-dd") << ": " << it.value() << "\n";
            }
            file.close();
        }
    }

    void loadCalendarDataFromFile(const QString &filePath) {
        if (!QFile::exists(filePath)) {
            qDebug() << "Файл не найден:" << filePath;
            return;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения:" << filePath;
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(": ");
            if (parts.size() == 2) {
                QDate date = QDate::fromString(parts[0], "yyyy-MM-dd");
                QString value = parts[1];
                if (date.isValid()) {
                    calendarData[date] = value;
                    qDebug() << "Загружена запись:" << date << value;
                } else {
                    qDebug() << "Неверный формат даты:" << parts[0];
                }
            } else {
                qDebug() << "Ошибка формата строки:" << line;
            }
        }
        file.close();
    }

public:
    explicit BaseWin(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~BaseWin() = default;
};


#endif //REPETITORPLATFORM_BASEWIN_H
