#include "authbase.h"
#include "../sha256/sha256.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AuthBase::AuthBase(QWidget *parent) : QWidget(parent) {}

QString AuthBase::hashPassword(const QString &password) {
    SHA256 sha256;
    sha256.update(reinterpret_cast<const unsigned char*>(password.toStdString().c_str()), password.length());
    unsigned char hash[SHA256::BLOCK_SIZE];
    sha256.final(hash);

    QString hashedPassword;
    for (int i = 0; i < SHA256::BLOCK_SIZE; ++i) {
        hashedPassword.append(QString("%1").arg(hash[i], 2, 16, QChar('0')).toLower());
    }
    return hashedPassword;
}

QMap<QString, QString> AuthBase::loadCredentials() {
    QMap<QString, QString> credentials;
    QFile file("C:\\pnya\\RepetitorPlatform\\src\\data\\credentials.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл с учетными данными.");
        return credentials;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 2) {
            credentials.insert(parts[0], parts[1]);
        }
    }

    file.close();
    return credentials;
}

bool AuthBase::saveCredential(const QString &login, const QString &hashedPassword) {
    QFile file("C:\\pnya\\RepetitorPlatform\\src\\data\\credentials.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << login << " " << hashedPassword << "\n";
        file.close();
        return true;
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return false;
    }
}