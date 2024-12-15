#ifndef AUTHERROR_H
#define AUTHERROR_H

#include "ErrorBase.h"
#include <QFile>
#include <QTextStream>

class AuthError : public ErrorBase {
public:
    explicit AuthError(const QString &message, const QString &context = QString());
    ~AuthError() override = default;

    void showError() const override; // Переопределение для отображения ошибки
    void logError(const QString &logFilePath) const; // Логирование ошибки в файл

    // Предустановленные ошибки
    static AuthError invalidCredentials();
    static AuthError missingFields();
    static AuthError passwordMismatch();
};

#endif // AUTHERROR_H
