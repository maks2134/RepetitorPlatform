#ifndef USER_H
#define USER_H

#include <QString>

class User {
private:
    QString username;
    QString password;

public:
    User(QString username, QString password);
    QString getUsername() const;
    QString getPassword() const;
};

#endif