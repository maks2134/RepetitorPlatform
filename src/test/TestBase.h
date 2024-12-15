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
    explicit TestBase(QWidget *parent = nullptr, const QString &filename = "");
    void loadTest(const QString &fileName);
    ~TestBase();


private:
    Ui::testBase *ui;
    void displayQuestion();
    void calculateResults();

private slots:
    void onNextButtonClicked();
    void onPreviousButtonClicked();
    void onFinishButtonClicked();
    void onReturnButtonClicked();
};

#endif // TESTBASE_H