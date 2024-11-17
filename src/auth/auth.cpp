#include "auth.h"
#include "../register/register.h"
#include "../main/mainwin.h"
#include "ui_Auth.h"
#include <QMessageBox>

Auth::Auth(QWidget *parent) :
        AuthBase(parent), ui(new Ui::Auth) {
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

    QString inputPasswordHash = hashPassword(password);
    QMap<QString, QString> credentials = loadCredentials();

    if (credentials.contains(login) && credentials.value(login) == inputPasswordHash) {
        QMessageBox::information(this, "Успех", "Успешная аутентификация.");
        mainWin *mainWindow = new mainWin();
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
    }
}

void Auth::onRegisterClicked() {
    Register *regWindow = new Register();
    regWindow->show();
    this->close();
}