#ifndef TESTBASE_H
#define TESTBASE_H

#include "NavigationManager.h"
#include <QWidget>

namespace Ui {
    class testBase;
}

class TestBase : public QWidget, public NavigationManager {
Q_OBJECT

public:
    explicit TestBase(QWidget *parent = nullptr);
    ~TestBase();

private:
    Ui::testBase *ui;
    void displayQuestion();
    void calculateResults();

private slots:
    void onNextButtonClicked();
    void onPreviousButtonClicked();
    void onFinishButtonClicked();
};

#endif // TESTBASE_H