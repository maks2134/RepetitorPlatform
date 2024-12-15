#ifndef REPETITORPLATFORM_REGISTER_H
#define REPETITORPLATFORM_REGISTER_H

#include "../authbase/authbase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE


class Register : public AuthBase{
Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register() override;

private slots:
    void onRegisterButtonClicked();
    void onAddTestButtonClicked();
    void onBackButtonClicked();
private:
    Ui::Register *ui;
    bool validateTestFile(const QString &filePath, const QString &subject);
};

#endif // REPETITORPLATFORM_REGISTER_H