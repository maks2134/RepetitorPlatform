#ifndef REPETITORPLATFORM_ACCOUNT_H
#define REPETITORPLATFORM_ACCOUNT_H

#include "../main/mainwin.h"
#include <QWidget>
#include "../basewin/basewin.h"
#include "../repetitors/Repetitor.h" // Подключаем класс репетитора

QT_BEGIN_NAMESPACE
namespace Ui { class account; }
QT_END_NAMESPACE

class account : public Repetitor { // Наследуемся от BaseWin
Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account() override;

private:
    Ui::account *ui;

    void displayItems();

private slots:
    void onDeleteButtonClicked();
};

#endif //REPETITORPLATFORM_ACCOUNT_H