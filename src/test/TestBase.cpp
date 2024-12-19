#include "TestBase.h"
#include "ui_testBase.h"
#include "../main/mainwin.h"
#include "../file/ResultFile.h"
#include <QMessageBox>
#include <QFile>
#include <QInputDialog>

TestBase::TestBase(QWidget *parent, const QString &filename) :
        QWidget(parent),
        ui(new Ui::testBase)
{
    ui->setupUi(this);
    loadQuestions(filename);
    userAnswers.resize(getTotalQuestions());
    displayQuestion();

    updateQuestionCounter();

    connect(ui->nextButton, &QPushButton::clicked, this, &TestBase::onNextButtonClicked);
    connect(ui->previousButton, &QPushButton::clicked, this, &TestBase::onPreviousButtonClicked);
    connect(ui->finishButton, &QPushButton::clicked, this, &TestBase::onFinishButtonClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &TestBase::onReturnButtonClicked);
}

TestBase::~TestBase() {
    delete ui;
}

void TestBase::displayQuestion() {
    if (getCurrentIndex() < 0 || getCurrentIndex() >= getTotalQuestions())
        return;

    ui->questionLabel->setText(getQuestion(getCurrentIndex()));
    ui->answerLineEdit->setText(getUserAnswer(getCurrentIndex()));

    updateQuestionCounter();  // Обновляем счетчик
}

void TestBase::onNextButtonClicked() {
    if (getCurrentIndex() >= getTotalQuestions() - 1) {
        QMessageBox::warning(this, "Warning", "Это последний вопрос.");
        return;
    }

    setUserAnswer(getCurrentIndex(), ui->answerLineEdit->text());
    nextQuestion();
    displayQuestion();  // displayQuestion вызовет updateQuestionCounter
}

void TestBase::onPreviousButtonClicked() {
    if (getCurrentIndex() <= 0) {
        QMessageBox::warning(this, "Warning", "Это первый вопрос.");
        return;
    }

    setUserAnswer(getCurrentIndex(), ui->answerLineEdit->text());
    previousQuestion();
    displayQuestion();  // displayQuestion вызовет updateQuestionCounter
}

void TestBase::onFinishButtonClicked() {
    setUserAnswer(getCurrentIndex(), ui->answerLineEdit->text());
    calculateResults();
}

void TestBase::calculateResults() {
    int correctCount = 0;
    int totalQuestions = getTotalQuestions();

    if (totalQuestions == 0) {
        QMessageBox::warning(this, "Error", "No questions available to calculate results.");
        return;
    }

    // Подсчет правильных ответов
    for (int i = 0; i < totalQuestions; ++i) {
        if (getUserAnswer(i).trimmed().toLower() == getCorrectAnswer(i).trimmed().toLower()) {
            correctCount++;
        }
    }

    // Вычисляем результат
    int grade = (correctCount * 100) / totalQuestions;  // Пример: процент правильных ответов

    // Формируем строку с результатом
    QString resultMessage = QString("Grade: %1%").arg(grade);

    // Запрашиваем имя пользователя
    bool ok;
    QString userName = QInputDialog::getText(nullptr, "Введите имя", "Ваше имя:", QLineEdit::Normal, "", &ok);

    if (!ok || userName.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Имя не введено. Результат не будет сохранен.");
        return;
    }

    // Показываем результат пользователю
    QMessageBox::information(this, "Results", resultMessage);

    // Создаем объект ResultFile для сохранения результатов
    ResultFile resultFile(R"(C:\pnya\RepetitorPlatform\src\data\result.txt)");
    resultFile.saveResult(userName, resultMessage);  // Сохраняем имя и результат
}



void TestBase::loadTest(const QString &fileName) {
    questions.clear();
    correctAnswers.clear();
    userAnswers.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 2) {
            questions.append(parts[0]);
            correctAnswers.append(parts[1]);
            userAnswers.append("");  // Initialize with empty answers
        }
    }

    file.close();

    if (questions.isEmpty()) {
        QMessageBox::warning(this, "Error", "No questions found in the test file.");
        return;
    }

    currentQuestionIndex = 0;
    displayQuestion();
    updateQuestionCounter();  // Обновляем счетчик вопросов
}

void TestBase::updateQuestionCounter() {
    if (!ui->questionCounterLabel) {
        qDebug() << "questionCounterLabel is not accessible!";
        return;
    }

    int totalQuestions = getTotalQuestions();
    if (totalQuestions == 0) {
        ui->questionCounterLabel->setText("Вопрос 0 из 0");
    } else {
        ui->questionCounterLabel->setText(QString("Вопрос %1 из %2")
                                                  .arg(getCurrentIndex() + 1)
                                                  .arg(totalQuestions));
    }
}

void TestBase::onReturnButtonClicked() {
    auto *mainWindow = new mainWin;  // Создаём новое окно mainWin
    mainWindow->show();
    this->close();  // Закрываем текущее окно
}