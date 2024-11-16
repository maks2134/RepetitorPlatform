#include "auth.h"
#include "../register/register.h"
#include "ui_Auth.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../sha256/sha256.h"

Auth::Auth(QWidget *parent) :
        QWidget(parent), ui(new Ui::Auth) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Auth::onLoginClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Auth::onRegisterClicked);
}

Auth::~Auth() {
    delete ui;
}

void Auth::onLoginClicked() {
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    // Hash the input password
    SHA256 sha256;
    sha256.update(reinterpret_cast<const unsigned char*>(password.toStdString().c_str()), password.length());
    unsigned char hash[SHA256::BLOCK_SIZE];
    sha256.final(hash);

    QString inputPasswordHash;
    for (int i = 0; i < SHA256::BLOCK_SIZE; ++i) {
        inputPasswordHash.append(QString("%1").arg(hash[i], 2, 16, QChar('0')).toLower());
    }

    QMap<QString, QString> credentials = loadCredentials();

    if (credentials.contains(login) && credentials.value(login) == inputPasswordHash) {
        QMessageBox::information(this, "Успех", "Успешная аутентификация.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
    }
}

void Auth::onRegisterClicked() {
    Register *regWindow = new Register();
    regWindow->show();
    this->close();
}

QMap<QString, QString> Auth::loadCredentials() {
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