#include "TestBase.h"
#include "ui_testBase.h"
#include <QMessageBox>

TestBase::TestBase(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::testBase)
{
    ui->setupUi(this);
    loadQuestions("C:\\pnya\\RepetitorPlatform\\src\\data\\questions.txt");
    userAnswers.resize(getTotalQuestions());
    displayQuestion();

    connect(ui->nextButton, &QPushButton::clicked, this, &TestBase::onNextButtonClicked);
    connect(ui->previousButton, &QPushButton::clicked, this, &TestBase::onPreviousButtonClicked);
    connect(ui->finishButton, &QPushButton::clicked, this, &TestBase::onFinishButtonClicked);
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
    for (int i = 0; i < getTotalQuestions(); ++i) {
        if (getUserAnswer(i).trimmed().toLower() == getCorrectAnswer(i).trimmed().toLower()) {
            correctCount++;
        }
    }

    QString resultMessage = QString("Correct Answers: %1/%2\nGrade: %3")
            .arg(correctCount)
            .arg(getTotalQuestions())
            .arg((correctCount * 10) / getTotalQuestions());

    QMessageBox::information(this, "Results", resultMessage);
}