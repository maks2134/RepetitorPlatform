#ifndef REPETITORPLATFORM_ADDTESTWIN_H
#define REPETITORPLATFORM_ADDTESTWIN_H

#include <QWidget>
#include "../exception/AuthError.h"
#include "../exception/CredentialFileError.h"
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>
#include <QFileDialog>
#include "Test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class addtestwin; }


class addtestwin : public QWidget {
Q_OBJECT

public:

    QList<Test>* listTest;
    QDate date;

    explicit addtestwin(QWidget *parent = nullptr);

    ~addtestwin() override;

private slots:
    void onAddTestButtonClicked();
    bool validateTestFile(const QString &filePath, const QString &subject);
    void closeEvent(QCloseEvent* event) override;
    signals:
    void addTestDestroyed();
private:
    Ui::addtestwin *ui;
};

QT_END_NAMESPACE

#endif //REPETITORPLATFORM_ADDTESTWIN_H
