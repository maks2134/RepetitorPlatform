#include "QuestionFile.h"
#include <QTextStream>

QuestionFile::QuestionFile(const QString &filePath) : File(filePath) {}

const QStringList &QuestionFile::getQuestions() const {
    return questions;
}

const QStringList &QuestionFile::getCorrectAnswers() const {
    return correctAnswers;
}

bool QuestionFile::load() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    questions.clear();
    correctAnswers.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 2) {
            questions.append(parts[0]);
            correctAnswers.append(parts[1]);
        }
    }

    file.close();
    return true;
}

bool QuestionFile::save() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < questions.size(); ++i) {
        out << questions[i] << ";" << correctAnswers[i] << "\n";
    }

    file.close();
    return true;
}

void QuestionFile::addQuestion(const QString &question, const QString &answer) {
    questions.append(question);
    correctAnswers.append(answer);
}
