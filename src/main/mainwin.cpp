#include "mainWin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

mainWin::mainWin(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainwin) {
    ui->setupUi(this);
    loadCalendarData("C:\\pnya\\RepetitorPlatform\\src\\data\\calendar.txt");
    setupCalendar();

    connect(ui->pushButton_5, &QPushButton::clicked, this, &mainWin::onTestButtonClicked);
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
                calendarData[date] = event;
            }
        }
    }
}

void mainWin::setupCalendar() {
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &mainWin::updateCalendar);
}

void mainWin::updateCalendar(const QDate &date) {
    if (calendarData.contains(date)) {
        QString event = calendarData.value(date);
        QMessageBox::information(this, "Event", event);
    } else {
        QMessageBox::information(this, "No Event", "No events for this date.");
    }
}

void mainWin::onTestButtonClicked() {
    TestBase *testWidget = new TestBase;
    testWidget->show();
    this->close();
}