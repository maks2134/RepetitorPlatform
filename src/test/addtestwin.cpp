
#include "addtestwin.h"
#include "ui_addtestwin.h"
#include "../file/TestFile.h"


addtestwin::addtestwin(QWidget *parent) :
        QWidget(parent), ui(new Ui::addtestwin) {
    ui->setupUi(this);
    connect(ui->pushButtonAddTest, &QPushButton::clicked, this, &addtestwin::onAddTestButtonClicked);

}

addtestwin::~addtestwin() {
    delete ui;
}

void addtestwin::onAddTestButtonClicked() {
    auto* testFile = new TestFile("C:\\pnya\\RepetitorPlatform\\src\\data\\test.txt");
    testFile->load();
    listTest = new QList<Test>(testFile->getList());

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

        auto* newtest = new Test(name, subject, date, QTime(), QDir::toNativeSeparators(destinationPath));
        listTest->append(*newtest);

        testFile->setList(*listTest);
        testFile->save();
        QMessageBox::information(this, "Успех", "Репетитор и файл теста успешно добавлены.");


    } catch (const AuthError &e) {
        e.showError();
    } catch (const CredentialFileError &e) {
        e.showError();
    }
}

bool addtestwin::validateTestFile(const QString &filePath, const QString &subject) {
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
            return false;
        }
    }
    file.close();
    return true;
}

void addtestwin::closeEvent(QCloseEvent *event) {
    emit addTestDestroyed();;
    QWidget::closeEvent(event);
}
