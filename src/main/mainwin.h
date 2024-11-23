#ifndef REPETITORPLATFORM_MAINWIN_H
#define REPETITORPLATFORM_MAINWIN_H

#include <QWidget>
#include <QCalendarWidget>
#include <QMap>
#include <QDate>
#include <ui_mainWin.h>
#include "../basewin/basewin.h"
#include "../test/testBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwin; }
QT_END_NAMESPACE

class mainWin : public BaseWin {  // Наследование
Q_OBJECT

public:
    explicit mainWin(QWidget *parent = nullptr);
    ~mainWin() override;

private:
    Ui::mainwin *ui;

    void loadCalendarData(const QString &fileName);
    void setupCalendar();

private slots:
    void updateCalendar(const QDate &date);
    void onTestButtonClicked();
    void onAccountButtonClicked();
    void onSearchButtonClicked();  // Новый слот для поиска

protected:
    QMap<QDate, QString> calendarData;
    void saveCalendarDataToFile(const QString &fileName);
};

#endif // REPETITORPLATFORM_MAINWIN_H