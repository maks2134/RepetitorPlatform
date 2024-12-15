#include "auth.h"
#include "../register/register.h"
#include "../main/mainwin.h"
#include "ui_Auth.h"
#include "../exception/AuthError.h"
#include "../exception/CredentialFileError.h"
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

    try {
        if (login.isEmpty() || password.isEmpty()) {
            throw AuthError::missingFields(); // Выбрасываем ошибку для пустых полей
        }

        QString inputPasswordHash = hashPassword(password);
        QMap<QString, QString> credentials = loadCredentials();

        if (credentials.contains(login) && credentials.value(login) == inputPasswordHash) {
            QMessageBox::information(this, "Успех", "Аутентификация прошла успешно.");
            mainWin *mainWindow = new mainWin();
            mainWindow->show();
            this->close();
        } else {
            throw AuthError::invalidCredentials(); // Выбрасываем ошибку для неверных данных
        }
    } catch (const AuthError &e) {
        e.showError(); // Показываем сообщение на русском языке
        e.logError("auth_errors.log"); // Логируем ошибку
    }
}


void Auth::onRegisterClicked() {
    Register *regWindow = new Register();
    regWindow->show();
    this->close();
}
