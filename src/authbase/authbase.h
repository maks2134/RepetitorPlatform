#ifndef AUTHBASE_H
#define AUTHBASE_H

#include <QWidget>
#include "../file/CredentialFile.h"
#include "../repetitors/Repetitor.h"
//public Repetitor,
class AuthBase :  public QWidget, public Repetitor{
Q_OBJECT

protected:
    CredentialFile credentialFile;

    explicit AuthBase(QWidget *parent = nullptr);

    // Хэширование пароля
    QString hashPassword(const QString &password);

    // Методы для работы с учетными данными
    bool saveCredential(const QString &login, const QString &hashedPassword);
    QMap<QString, QString> loadCredentials();

    // Абстрактный метод для заполнения данных репетитора
   // virtual void fillRepetitorInfo(const QString &name, const QString &subject, const QDate &availableDate) = 0;
};

#endif // AUTHBASE_H
