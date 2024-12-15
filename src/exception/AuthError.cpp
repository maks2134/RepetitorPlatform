#include "AuthError.h"
#include <QMessageBox>
#include <QDebug>

AuthError::AuthError(const QString &message, const QString &context)
        : ErrorBase(message, context) {}

// Реализация отображения ошибки на русском языке
void AuthError::showError() const {
    QString fullMessage = "Ошибка аутентификации: " + message;
    if (!context.isEmpty()) {
        fullMessage += "\nКонтекст: " + context;
    }
    QMessageBox::warning(nullptr, "Ошибка аутентификации", fullMessage);
}

// Логирование ошибки в файл
void AuthError::logError(const QString &logFilePath) const {
    QFile logFile(logFilePath);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << "Ошибка аутентификации: " << message << "\n";
        if (!context.isEmpty()) {
            out << "Контекст: " << context << "\n";
        }
        out << "--------------------------\n";
        logFile.close();
    } else {
        qDebug() << "Не удалось открыть файл журнала: " << logFilePath;
    }
}

// Предустановленные ошибки с сообщениями на русском языке
AuthError AuthError::invalidCredentials() {
    return AuthError("Неверный логин или пароль.", "Проверьте введенные учетные данные.");
}

AuthError AuthError::missingFields() {
    return AuthError("Не заполнены обязательные поля.", "Убедитесь, что все поля заполнены.");
}

AuthError AuthError::passwordMismatch() {
    return AuthError("Пароли не совпадают.", "Убедитесь, что введенные пароли совпадают.");
}
