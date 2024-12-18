#include "TestBase.h"
#include "ui_testBase.h"
#include "../main/mainwin.h"
#include <QMessageBox>
#include <QFile>

TestBase::TestBase(QWidget *parent, const QString &filename) :
        QWidget(parent),
        ui(new Ui::testBase)
{
    ui->setupUi(this);
    loadQuestions(filename);
    userAnswers.resize(getTotalQuestions());
    displayQuestion();

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
}

void TestBase::onNextButtonClicked() {
    setUserAnswer(getCurrentIndex(), ui->answerLineEdit->text());
    nextQuestion();
    displayQuestion();
}

void TestBase::onPreviousButtonClicked() {
    setUserAnswer(getCurrentIndex(), ui->answerLineEdit->text());
    previousQuestion();
    displayQuestion();
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

    for (int i = 0; i < totalQuestions; ++i) {
        if (getUserAnswer(i).trimmed().toLower() == getCorrectAnswer(i).trimmed().toLower()) {
            correctCount++;
        }
    }

    QString resultMessage = QString("Correct Answers: %1/%2\nGrade: %3")
            .arg(correctCount)
            .arg(totalQuestions)
            .arg((correctCount * 10) / totalQuestions);

    QMessageBox::information(this, "Results", resultMessage);
}

void TestBase::loadTest(const QString &fileName) {
    questions.clear();
    correctAnswers.clear();
    userAnswers.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the test file.");
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
}

void TestBase::onReturnButtonClicked() {
    auto *mainWindow = new mainWin;  // Создаём новое окно mainWin
    mainWindow->show();
    this->close();  // Закрываем текущее окно
}
