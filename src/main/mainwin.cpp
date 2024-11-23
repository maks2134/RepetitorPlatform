#include "mainWin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../account/account.h"

mainWin::mainWin(QWidget *parent) :
        BaseWin(parent), ui(new Ui::mainwin) {
    ui->setupUi(this);

    // Установка имени, предмета и даты из базового класса
    setName("Default Name");
    setSubject("Default Subject");
    setAvailableDate(QDate::currentDate());

    loadCalendarData("C:\\pnya\\RepetitorPlatform\\src\\data\\calendar.txt");
    setupCalendar();

    connect(ui->pushButton_4, &QPushButton::clicked, this, &mainWin::onAccountButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &mainWin::onTestButtonClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &mainWin::onSearchButtonClicked);
}

mainWin::~mainWin() {
    delete ui;
}

void mainWin::loadCalendarData(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 2) {
            QDate date = QDate::fromString(parts[0], "yyyy-MM-dd");
            QString event = parts[1];
            if (date.isValid()) {
                addEvent(date, event);  // Используем метод из Repetitor
            }
        }
    }
}

void mainWin::setupCalendar() {
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &mainWin::updateCalendar);
}

void mainWin::updateCalendar(const QDate &date) {
    QString event = getEvent(date);  // Используем метод из Repetitor
    if (!event.isEmpty()) {
        QMessageBox::information(this, "Event", event);
    } else {
        QMessageBox::information(this, "No Event", "No events for this date.");
    }
}

void mainWin::saveCalendarDataToFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for writing");
        return;
    }

    QTextStream out(&file);
    QMap<QDate, QString> events = getAllEvents();
    for (auto it = events.begin(); it != events.end(); ++it) {
        out << it.key().toString("yyyy-MM-dd") << "," << it.value() << "\n";
    }
    file.close();
}

void mainWin::onAccountButtonClicked() {
    saveCalendarDataToFile("C:\\pnya\\RepetitorPlatform\\src\\data\\items.txt");
    account *accountWidget = new account;
    accountWidget->show();
    this->close();
}

void mainWin::onTestButtonClicked() {
    TestBase *testWidget = new TestBase;
    testWidget->show();
    this->close();
}

void mainWin::onSearchButtonClicked() {
    QString subject = ui->lineEdit->text().trimmed();
    if (subject.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a subject to search");
        return;
    }

    if (getSubject() == subject) {
        QMessageBox::information(this, "Repetitor Found", "Name: " + getName() +
                                                          "\nDate: " + getAvailableDate().toString("yyyy-MM-dd"));
    } else {
        QMessageBox::information(this, "No Results", "No repetitor found for this subject.");
    }
}