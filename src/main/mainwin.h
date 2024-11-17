#ifndef REPETITORPLATFORM_MAINWIN_H
#define REPETITORPLATFORM_MAINWIN_H

#include <QWidget>
#include <QCalendarWidget>
#include <QMap>
#include <QDate>
#include <ui_mainWin.h>
#include "../test/testBase.h"  // Include your test window header

QT_BEGIN_NAMESPACE
namespace Ui { class mainwin; }
QT_END_NAMESPACE

class mainWin : public QWidget {
Q_OBJECT

public:
    explicit mainWin(QWidget *parent = nullptr);
    ~mainWin() override;

private:
    Ui::mainwin *ui;
    QMap<QDate, QString> calendarData;

    void loadCalendarData(const QString &fileName);
    void setupCalendar();

private slots:
    void updateCalendar(const QDate &date);
    void onTestButtonClicked();
};

#endif // REPETITORPLATFORM_MAINWIN_H