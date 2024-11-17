#include "register.h"
#include "ui_Register.h"
#include "../auth/auth.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
        AuthBase(parent),
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

    QString hashedPassword = hashPassword(password);

    if (saveCredential(login, hashedPassword)) {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно");

        Auth *authWindow = new Auth();
        authWindow->show();
        this->close();
    }
}