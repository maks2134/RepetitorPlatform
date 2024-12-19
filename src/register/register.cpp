#include "register.h"
#include "ui_Register.h"
#include "../auth/auth.h"
#include "../exception/AuthError.h"

#include "../test/addtestwin.h"
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>


Register::Register(QWidget *parent) :
        AuthBase(parent),
        ui(new Ui::Register) {
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Register::onRegisterButtonClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Register::onBackButtonClicked); // Подключение кнопки "Назад"

}

Register::~Register() {
    delete ui;
}

void Register::onRegisterButtonClicked() {
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString confirmPassword = ui->lineEdit_3->text();

    // Регулярное выражение для проверки на отсутствие пробелов в логине
    QRegularExpression regex("^\\S+$"); // ^\S+$ означает, что строка не содержит пробелов

    if (!regex.match(login).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Логин не должен содержать пробелы.");
        return;
    }

    try {
        if (login.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            throw AuthError::missingFields(); // Ошибка: пустые поля
        }

        if (password != confirmPassword) {
            throw AuthError::passwordMismatch(); // Ошибка: пароли не совпадают
        }

        QString hashedPassword = hashPassword(password);

        if (saveCredential(login, hashedPassword)) {
            QMessageBox::information(this, "Успех", "Регистрация пользователя прошла успешно.");

            Auth *authWindow = new Auth(); // Создаём окно входа
            authWindow->show();            // Показываем его
            this->close();                 // Закрываем текущее окно
        }
    } catch (const AuthError &e) {
        e.showError(); // Показываем сообщение об ошибке
        e.logError("auth_errors.log"); // Логируем ошибку
    }
}

void Register::onBackButtonClicked() {
    Auth *authWindow = new Auth(); // Создаём окно входа
    authWindow->show();            // Показываем его
    this->close();                 // Закрываем текущее окно
}


