#include "NavigationManager.h"

NavigationManager::NavigationManager() : currentQuestionIndex(0) {
    userAnswers.resize(getTotalQuestions());
}

QString NavigationManager::getUserAnswer(int index) const {
    return userAnswers.value(index);
}

void NavigationManager::setUserAnswer(int index, const QString &answer) {
    if (index >= 0 && index < userAnswers.size()) {
        userAnswers[index] = answer;
    }
}

int NavigationManager::getCurrentIndex() const {
    return currentQuestionIndex;
}

void NavigationManager::nextQuestion() {
    if (currentQuestionIndex < userAnswers.size() - 1) {
        currentQuestionIndex++;
    }
}

void NavigationManager::previousQuestion() {
    if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
    }
}