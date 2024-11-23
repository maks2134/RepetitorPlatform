#include "account.h"
#include "ui_account.h"
#include <QMessageBox>

account::account(QWidget *parent) :
        BaseWin(parent), // Наследуемся от BaseWin
        ui(new Ui::account) {
    ui->setupUi(this); // Загружаем интерфейс account
    loadCalendarDataFromFile("C:\\pnya\\RepetitorPlatform\\src\\data\\items.txt");
    // Подключаем кнопку "Удалить" к слоту
    connect(ui->pushButton_2, &QPushButton::clicked, this, &account::onDeleteButtonClicked);

    // Отображаем все предметы
    displayItems();
}

account::~account() {
    delete ui;
}

void account::displayItems() {
    QString allItems;
    qDebug() << "Содержимое calendarData:" << calendarData;
    if (calendarData.isEmpty()) {
        allItems = "Нет данных для отображения.";
    } else {
        for (auto it = calendarData.begin(); it != calendarData.end(); ++it) {
            allItems += it.key().toString("yyyy-MM-dd") + ": " + it.value() + "\n";
        }
    }

    // Устанавливаем текст в label
    ui->label_2->setText(allItems);
}

void account::onDeleteButtonClicked() {
    QString itemToDelete = ui->lineEdit->text();
    bool found = false;

    // Удаляем предмет из calendarData
    for (auto it = calendarData.begin(); it != calendarData.end();) {
        if (it.value() == itemToDelete) {
            it = calendarData.erase(it);
            found = true;
        } else {
            ++it;
        }
    }

    if (found) {
        // Сохраняем данные в файл
        saveCalendarDataToFile("C:\\pnya\\RepetitorPlatform\\src\\data\\items.txt");
        QMessageBox::information(this, "Success", "Item deleted successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Item not found!");
    }

    // Обновляем отображение предметов
    displayItems();
}