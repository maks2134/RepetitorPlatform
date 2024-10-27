#include "UserController.h"
#include <QFile>
#include <QTextStream>

UserController::UserController(const QString& filePath) {
    loadUsersFromFile(filePath);
}

void UserController::loadUsersFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Обработка ошибки открытия файла
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(",");
        if (userData.size() == 2) {
            users.append(User(userData[0], userData[1]));
        }
    }
    file.close();
}

bool UserController::login(const QString& username, const QString& password) {
    for (const User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;  // Успешный вход
        }
    }
    return false;  // Неправильные данные
}