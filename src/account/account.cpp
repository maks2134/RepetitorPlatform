#include "account.h"
#include "ui_account.h"
#include <QMessageBox>

account::account(QWidget *parent) :
        BaseWin(parent), // Наследуемся от BaseWin
        ui(new Ui::account) {
    ui->setupUi(this); // Загружаем интерфейс account
    loadCalendarDataFromFile(R"(C:\pnya\RepetitorPlatform\src\data\repetitors.txt)");
    // Подключаем кнопку "Удалить" к слоту
    connect(ui->pushButton_2, &QPushButton::clicked, this, &account::onDeleteButtonClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &account::onReturnButtonClicked);
    // Отображаем все предметы
    displayItems();
}

account::~account() {
    delete ui;
}

void account::displayItems() {
    ui->listWidget->clear(); // Очистка списка перед обновлением

    QString subjectInput = ui->subjectInputLineEdit->text().trimmed();

    if (subjectInput.isEmpty()) {
//        ui->statusLabel->setText("Введите название предмета.");
        return;
    }

    if (!subjectRepetitors.contains(subjectInput)) {
//        ui->statusLabel->setText("Нет репетиторов по данному предмету.");
        return;
    }

//    ui->statusLabel->clear();
    const QVector<QString> &repetitors = subjectRepetitors[subjectInput];

    for (const QString &name : repetitors) {
        QListWidgetItem *item = new QListWidgetItem(name, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked); // Добавляем чекбокс для подтверждения
    }
}



void account::onDeleteButtonClicked() {
    QString subjectInput = ui->subjectInputLineEdit->text().trimmed();

    if (!subjectRepetitors.contains(subjectInput)) {
//        ui->statusLabel->setText("Нет такого предмета для удаления.");
        return;
    }

    QVector<QString> &repetitors = subjectRepetitors[subjectInput];
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();

    for (QListWidgetItem *item : selectedItems) {
        QString nameToDelete = item->text();
        repetitors.removeAll(nameToDelete); // Удаляем репетитора из данных
        delete item; // Удаляем элемент из интерфейса
    }

//    ui->statusLabel->setText("Репетитор удалён.");
    saveRepetitorsToFile(R"(D:\Clion\RepetitorPlatform-main\RepetitorPlatform\src\data\repetitors.txt)"); // Сохранение изменений
}



void account::onReturnButtonClicked() {
    mainWin *mainWindow = new mainWin;  // Создаём новое окно mainWin
    mainWindow->show();
    this->close();  // Закрываем текущее окно
}

void account::loadRepetitorsFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << fileName;
        return;
    }

    subjectRepetitors.clear(); // Очищаем текущие данные

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");
        if (parts.size() >= 2) { // Достаточно 2 частей: предмет и имя репетитора
            QString subject = parts[0].trimmed();
            QString tutorName = parts[1].trimmed();

            // Добавляем имя репетитора в список по предмету
            subjectRepetitors[subject].append(tutorName);
        }
    }

    file.close();
    displayItems(); // Обновляем отображение
}



void account::saveRepetitorsToFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for saving:" << fileName;
        return;
    }

    QTextStream out(&file);

    for (auto it = subjectRepetitors.begin(); it != subjectRepetitors.end(); ++it) {
        const QString &subject = it.key();
        for (const QString &name : it.value()) {
            out << subject << ";" << name << "\n";
        }
    }

    file.close();
}