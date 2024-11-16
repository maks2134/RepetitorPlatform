#include "register.h"
#include "ui_Register.h"
#include "../auth/auth.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../sha256/sha256.h"

Register::Register(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Register::onRegisterButtonClicked);
}

Register::~Register() {
    delete ui;
}

void Register::onRegisterButtonClicked() {
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString confirmPassword = ui->lineEdit_3->text();

    if (login.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают");
        return;
    }

    // Hash the password
    SHA256 sha256;
    sha256.update(reinterpret_cast<const unsigned char*>(password.toStdString().c_str()), password.length());
    unsigned char hash[SHA256::BLOCK_SIZE];
    sha256.final(hash);

    QString hashedPassword;
    for (int i = 0; i < SHA256::BLOCK_SIZE; ++i) {
        hashedPassword.append(QString("%1").arg(hash[i], 2, 16, QChar('0')).toLower());
    }

    QFile file("C:\\pnya\\RepetitorPlatform\\src\\data\\credentials.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << login << " " << hashedPassword << "\n";
        file.close();

        QMessageBox::information(this, "Успех", "Регистрация прошла успешно");

        Auth *authWindow = new Auth();
        authWindow->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
    }
}