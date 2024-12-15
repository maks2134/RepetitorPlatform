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


QT_BEGIN_NAMESPACE
namespace Ui { class mainwin; }
QT_END_NAMESPACE

class mainWin : public BaseWin {  // Наследование
Q_OBJECT

public:
    explicit mainWin(QWidget *parent = nullptr);
    ~mainWin() override;
    void loadRepetitors(const QString &fileName); // Загрузка репетиторов

private:
    Ui::mainwin *ui;
    BinarySearchTree<QString, QVector<Repetitor>> subjectTree;
    void loadCalendarData(const QString &fileName);

private slots:
    void onTestButtonClicked();
    void onAccountButtonClicked();
    void onSearchButtonClicked();                 // Поиск репетиторов по предмету
    void onRepetitorSelected(QListWidgetItem *);  // Обработка выбора репетитора

protected:
    QMap<QDate, QString> calendarData;

};

#endif // REPETITORPLATFORM_MAINWIN_H