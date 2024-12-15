#include "AuthBase.h"
#include "../sha256/sha256.h"
#include <QMessageBox>

AuthBase::AuthBase(QWidget *parent)
        : QWidget(parent), credentialFile("C:\\pnya\\RepetitorPlatform\\src\\data\\credentials.txt") {
    // Загрузка учетных данных
    if (!credentialFile.load()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить учетные данные.");
    }
}

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

bool AuthBase::saveCredential(const QString &login, const QString &hashedPassword) {
    credentialFile.addCredential(login, hashedPassword);
    return credentialFile.save();
}

QMap<QString, QString> AuthBase::loadCredentials() {
    return credentialFile.getCredentials();
}
