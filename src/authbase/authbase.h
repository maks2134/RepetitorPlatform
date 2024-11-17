#ifndef AUTHBASE_H
#define AUTHBASE_H

#include <QWidget>
#include <QString>
#include <QMap>

class AuthBase : public QWidget {
Q_OBJECT

public:
    explicit AuthBase(QWidget *parent = nullptr);
    virtual ~AuthBase() = default;

protected:
    QString hashPassword(const QString &password);
    QMap<QString, QString> loadCredentials();
    bool saveCredential(const QString &login, const QString &hashedPassword);
};

#endif // AUTHBASE_H
