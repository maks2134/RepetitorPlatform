#ifndef REPETITORPLATFORM_ACCOUNT_H
#define REPETITORPLATFORM_ACCOUNT_H

#include "../main/mainwin.h"
#include <QWidget>
#include "../basewin/basewin.h"
#include "../repetitors/Repetitor.h" // Подключаем класс репетитора
#include <QMap> // Для хранения предметов и репетиторов

QT_BEGIN_NAMESPACE
namespace Ui { class account; }
QT_END_NAMESPACE

class account : public BaseWin { // Наследуемся от BaseWin
Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();

private:
    Ui::account *ui;
    QMap<QString, QVector<QString>> subjectRepetitors; // Карта: предмет -> список репетиторов

    void loadRepetitorsFromFile(const QString &fileName); // Загрузка данных
    void saveRepetitorsToFile(const QString &fileName);   // Сохранение данных
    void displayItems();                                  // Отображение предметов и репетиторов

private slots:
    void onDeleteButtonClicked();
    void onReturnButtonClicked();
};

#endif //REPETITORPLATFORM_ACCOUNT_H
