#ifndef REPETITORPLATFORM_MAINWIN_H
#define REPETITORPLATFORM_MAINWIN_H

#include <QWidget>
#include <QCalendarWidget>
#include <QMap>
#include <QDate>
#include <ui_mainWin.h>
#include <QListWidgetItem>
#include "../basewin/basewin.h"
#include "../test/testBase.h"
#include "../finder/RepetitorSearchWidget.h"
#include "../test/Test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwin; }
QT_END_NAMESPACE

class mainWin : public BaseWin {  // Наследование
Q_OBJECT

public:
    explicit mainWin(QWidget *parent = nullptr);
    ~mainWin() override;
    QDate selectedDate;
    QList<Test>* listTest;

private:
    Ui::mainwin *ui;
    BinarySearchTree<QString, QVector<Test>> testTree;
    void loadCalendarData(const QString &fileName);

private slots:
    void onTestButtonClicked();
    void onAccountButtonClicked();
    void searchTests(const QString &query);                 // Поиск репетиторов по предмету
    void onRepetitorSelected(QListWidgetItem *);  // Обработка выбора репетитора
    void onCalendarClicked(QDate date);
    void addTestClicked();
protected:
    QMap<QDate, QString> calendarData;

};

#endif // REPETITORPLATFORM_MAINWIN_H