#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../models/User.h"
#include <QList>
#include <QString>

class UserController {
private:
    QList<User> users;  // Список всех пользователей

    void loadUsersFromFile(const QString& filePath); // Метод для загрузки пользователей из файла

public:
    UserController(const QString& filePath);
    bool login(const QString& username, const QString& password);
};

#endif // USERCONTROLLER_H