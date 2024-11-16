#ifndef REPETITORPLATFORM_REGISTER_H
#define REPETITORPLATFORM_REGISTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QWidget {
Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register() override;

private slots:
    void onRegisterButtonClicked();

private:
    Ui::Register *ui;
};

#endif // REPETITORPLATFORM_REGISTER_H