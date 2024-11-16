#ifndef REPETITORPLATFORM_AUTH_H
#define REPETITORPLATFORM_AUTH_H

#include <QWidget>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class Auth; }
QT_END_NAMESPACE

class Auth : public QWidget {
Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth() override;

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::Auth *ui;
    QMap<QString, QString> loadCredentials();
};

#endif //REPETITORPLATFORM_AUTH_H