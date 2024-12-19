#include "mainWin.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../account/account.h"
#include "../file/TestFile.h"
#include "../test/addtestwin.h"


mainWin::mainWin(QWidget *parent) :
        BaseWin(parent), ui(new Ui::mainwin) {
    ui->setupUi(this);

    auto* testFile = new TestFile(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");
    testFile->load();
    listTest = new QList<Test>(testFile->getList());
    ui->repetitorListWidget->setSortingEnabled(true);
    ui->searchLineEdit->setPlaceholderText("Введите данные");
    for(auto& elem : *listTest){
        qDebug() << elem.getDate();
    }

    loadCalendarData(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");

    connect(ui->pushButton_4, &QPushButton::clicked, this, &mainWin::onAccountButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, [&]() {
        QString query = ui->searchLineEdit->text(); // Получаем текст из поля ввода
        searchTests(query); // Выполняем поиск
    });
    connect(ui->repetitorListWidget, &QListWidget::itemDoubleClicked, this, &mainWin::onRepetitorSelected);
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &mainWin::onCalendarClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &mainWin::addTestClicked);
}

mainWin::~mainWin() {
    delete ui;
}

void mainWin::loadCalendarData(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open calendar file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.size() < 5) continue;

        QString name = parts[0];   // Имя репетитора
        QString subject = parts[1]; // Предмет
        QDate date = QDate::fromString(parts[2], "dd.MM.yyyy");
        QString filePath = parts[4]; // Путь к файлу

        Test test(name, subject, date, QTime(), filePath);

        // Добавляем тест в дерево с разными ключами
        testTree[name].append(test);       // По имени репетитора
        testTree[subject].append(test);    // По предмету
        testTree[date.toString("dd.MM.yyyy")].append(test); // По дате
    }
    file.close();
}


void mainWin::onAccountButtonClicked() {
    saveCalendarDataToFile(R"(C:\pnya\RepetitorPlatform\src\data\items.txt)");
    account *accountWidget = new account;
    accountWidget->show();
    this->close();
}

void mainWin::onTestButtonClicked() {
    TestBase *testWidget = new TestBase;
    testWidget->show();
    this->close();
}




void mainWin::onRepetitorSelected(QListWidgetItem *item) {
    QString testFilePath = item->data(Qt::UserRole).toString();
    auto *testWidget = new TestBase;
    testWidget->loadTest(testFilePath);
    testWidget->show();
    this->close();
}

void mainWin::searchTests(const QString &query) {
    ui->repetitorListWidget->clear(); // Очистка списка перед отображением результатов

    QSet<QString> addedItems; // Множество для отслеживания уже добавленных результатов
    bool found = false;

    // Проход по всем элементам testTree
    for (auto it = testTree.begin(); it != testTree.end(); ++it) {
        const QVector<Test> &tests = it.value();
        for (const auto &test : tests) {
            // Проверяем условия поиска
            if (test.getName() == query || test.getSubject() == query ||
                test.getDate().toString("dd.MM.yyyy") == query) {

                QString testIdentifier = test.getName() + "|" + test.getDate().toString("dd.MM.yyyy");

                if (!addedItems.contains(testIdentifier)) {
                    QListWidgetItem *item = new QListWidgetItem(test.getName());
                    item->setData(Qt::UserRole, test.getTestFilePath());
                    ui->repetitorListWidget->addItem(item);
                    addedItems.insert(testIdentifier);
                    found = true;
                }
            }
        }
    }

    if (!found) {
        QMessageBox::information(this, "Search Result", "No tests found for the given query.");
    }
}


void mainWin::onCalendarClicked(QDate date) {
    selectedDate = date; // Сохраняем выбранную дату
    ui->repetitorListWidget->clear(); // Очищаем список перед отображением результатов

    QString dateKey = date.toString("dd.MM.yyyy"); // Преобразуем дату в ключ
    if (testTree.contains(dateKey)) { // Проверяем, есть ли ключ в дереве
        const QVector<Test> &tests = testTree[dateKey]; // Получаем список тестов по ключу
        QSet<QString> addedItems; // Множество для отслеживания уникальных результатов

        for (const auto &test : tests) {
            QString testIdentifier = test.getName() + "|" + test.getTestFilePath(); // Уникальный идентификатор

            if (!addedItems.contains(testIdentifier)) { // Проверяем на дубликаты
                QListWidgetItem *item = new QListWidgetItem(test.getName());
                item->setData(Qt::UserRole, test.getTestFilePath());
                ui->repetitorListWidget->addItem(item);
                addedItems.insert(testIdentifier); // Добавляем в множество
            }
        }
    } else {
        QMessageBox::information(this, "No Tests", "No tests scheduled for this date.");
    }
}


void mainWin::addTestClicked() {
    auto* addTest = new addtestwin();
    addTest->date = selectedDate;

    addTest->show();
    connect(addTest, &addtestwin::addTestDestroyed, this, [&](){
        auto* testFile = new TestFile(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");
        testFile->load();
        listTest = new QList<Test>(testFile->getList());
        loadCalendarData(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");
        onCalendarClicked(selectedDate);
    });
}

