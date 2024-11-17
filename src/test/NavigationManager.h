#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include "QuestionManager.h"

class NavigationManager : public QuestionManager {
public:
    NavigationManager();
    QString getUserAnswer(int index) const;
    void setUserAnswer(int index, const QString &answer);
    int getCurrentIndex() const;
    void nextQuestion();
    void previousQuestion();

protected:
    QVector<QString> userAnswers;
    int currentQuestionIndex;
};

#endif // NAVIGATIONMANAGER_H