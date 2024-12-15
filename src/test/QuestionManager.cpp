#include "QuestionManager.h"
#include <QFile>
#include <QMessageBox>

QString QuestionManager::getQuestion(int index) const {
    return questions.value(index);
}

QString QuestionManager::getCorrectAnswer(int index) const {
    return correctAnswers.value(index);
}

int QuestionManager::getTotalQuestions() const {
    return questions.size();
}

void QuestionManager::loadQuestions(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Cannot open questions file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 2) {
            questions.append(parts[0]);
            correctAnswers.append(parts[1]);
        }
    }
}