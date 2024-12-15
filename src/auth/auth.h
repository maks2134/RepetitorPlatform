#ifndef REPETITORPLATFORM_AUTH_H
#define REPETITORPLATFORM_AUTH_H

#include <QWidget>
#include <QMap>
#include "../authbase/authbase.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Auth; }
QT_END_NAMESPACE

class Auth : public AuthBase{
Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth() override;

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::Auth *ui;
};

#endif //REPETITORPLATFORM_AUTH_H