#include "mainWin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../account/account.h"

mainWin::mainWin(QWidget *parent) :
        BaseWin(parent), ui(new Ui::mainwin) {
    ui->setupUi(this);

    loadRepetitors("C:\\pnya\\RepetitorPlatform\\src\\data\\repetitors.txt");
    loadCalendarData("C:\\pnya\\RepetitorPlatform\\src\\data\\calendar.txt");

    connect(ui->pushButton_4, &QPushButton::clicked, this, &mainWin::onAccountButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &mainWin::onSearchButtonClicked);
    connect(ui->repetitorListWidget, &QListWidget::itemDoubleClicked, this, &mainWin::onRepetitorSelected);
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


void mainWin::loadRepetitors(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open repetitors file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 3) {
            QString name = parts[0];
            QString subject = parts[1];
            QString testFilePath = parts[2];

            Repetitor repetitor(name, subject, testFilePath);
            if (subjectTree.contains(subject)) {
                subjectTree[subject].append(repetitor);
            } else {
                subjectTree.add(subject, {repetitor});
            }
        }
    }
}


void mainWin::onRepetitorSelected(QListWidgetItem *item) {
    QString testFilePath = item->data(Qt::UserRole).toString();
    TestBase *testWidget = new TestBase;
    testWidget->loadTest(testFilePath);
    testWidget->show();
    this->close();
}

void mainWin::onSearchButtonClicked() {
    // Implement the functionality of the method here
    QString subject = ui->searchLineEdit->text();
    ui->repetitorListWidget->clear();

    if (subjectTree.contains(subject)) {
        auto repetitors = subjectTree[subject];
        for (const auto &repetitor : repetitors) {
            QListWidgetItem *item = new QListWidgetItem(repetitor.name);
            item->setData(Qt::UserRole, repetitor.testFilePath);
            ui->repetitorListWidget->addItem(item);
        }
    } else {
        QMessageBox::information(this, "Search Result", "No repetitors found for this subject.");
    }
}

