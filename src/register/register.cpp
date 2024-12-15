#include "register.h"
#include "ui_Register.h"
#include "../auth/auth.h"
#include "../exception/AuthError.h"
#include "../exception/CredentialFileError.h"
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>
#include <QFileDialog>

Register::Register(QWidget *parent) :
        AuthBase(parent),
        ui(new Ui::Register) {
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Register::onRegisterButtonClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Register::onBackButtonClicked); // Подключение кнопки "Назад"
    connect(ui->pushButtonAddTest, &QPushButton::clicked, this, &Register::onAddTestButtonClicked); // Кнопка для добавления тестов репетиторов

    // Поля для тестов репетитора остаются выключенными
    ui->lineEditName->setEnabled(true);
    ui->lineEditSubject->setEnabled(true);
}

Register::~Register() {
    delete ui;
}

void Register::onRegisterButtonClicked() {
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString confirmPassword = ui->lineEdit_3->text();

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

            Auth *authWindow = new Auth();
            authWindow->show();
            this->close();
        }
    } catch (const AuthError &e) {
        e.showError(); // Показываем сообщение об ошибке
        e.logError("auth_errors.log"); // Логируем ошибку
    }
}

void Register::onAddTestButtonClicked() {
    QString name = ui->lineEditName->text();
    QString subject = ui->lineEditSubject->text();
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл теста", "", "Текстовые файлы (*.txt)");

    try {
        if (name.isEmpty() || subject.isEmpty()) {
            throw AuthError::missingFields(); // Ошибка: пустые поля для репетитора
        }

        if (filePath.isEmpty()) {
            throw AuthError("Вы не выбрали файл теста.");
        }

        // Проверяем и валидируем файл теста
        if (!validateTestFile(filePath, subject)) {
            throw AuthError("Файл не прошел проверку. Проверьте название и содержимое файла.");
        }

        // Указываем папку, куда будет скопирован файл
        QString destinationFolder = R"(C:\pnya\RepetitorPlatform\src\data\)";
        QString destinationPath = destinationFolder + QFileInfo(filePath).fileName();

        // Копируем файл в папку data
        if (!QFile::copy(filePath, destinationPath)) {
            throw CredentialFileError("Не удалось сохранить файл теста в папку data.");
        }

        // Сохраняем данные репетитора и полный путь к скопированному файлу
        QFile tutorFile(R"(C:\pnya\RepetitorPlatform\src\data\repetitors.txt)");
        if (!tutorFile.open(QIODevice::Append | QIODevice::Text)) {
            throw CredentialFileError("Не удалось открыть файл repetitors.txt для записи.");
        }

        QTextStream out(&tutorFile);
        out << name << ";" << subject << ";" << QDir::toNativeSeparators(destinationPath) << "\n";
        tutorFile.close();

        QMessageBox::information(this, "Успех", "Репетитор и файл теста успешно добавлены.");

        // Очищаем поля после успешного добавления
        ui->lineEditName->clear();
        ui->lineEditSubject->clear();
    } catch (const AuthError &e) {
        e.showError();
    } catch (const CredentialFileError &e) {
        e.showError();
    }
}

void Register::onBackButtonClicked() {
    Auth *authWindow = new Auth(); // Создаём окно входа
    authWindow->show();            // Показываем его
    this->close();                 // Закрываем текущее окно
}

bool Register::validateTestFile(const QString &filePath, const QString &subject) {
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла.";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() != 2 || parts[0].isEmpty() || parts[1].isEmpty()) {
            qDebug() << "Ошибка в строке файла: " << line;
            return false; // Если формат строки некорректен
        }
    }
    file.close();
    return true;
}
