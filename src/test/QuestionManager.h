#ifndef QUESTIONMANAGER_H
#define QUESTIONMANAGER_H

#include <QVector>
#include <QString>

class QuestionManager {
public:
    void loadQuestions(const QString &fileName);
    QString getQuestion(int index) const;
    QString getCorrectAnswer(int index) const;
    int getTotalQuestions() const;

protected:
    QVector<QString> questions;
    QVector<QString> correctAnswers;
};

#endif // QUESTIONMANAGER_H