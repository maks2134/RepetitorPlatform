#ifndef REPETITORSEARCHWIDGET_H
#define REPETITORSEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include "../finder/BinarySearchTree.h"
#include "../repetitors/Repetitor.h"

class RepetitorSearchWidget : public QWidget {
Q_OBJECT

public:
    explicit RepetitorSearchWidget(QWidget *parent = nullptr);
    void setSubjectTree(BinarySearchTree<QString, QVector<Repetitor>> *tree);  // Add this line

private:
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QListWidget *repetitorListWidget;
    BinarySearchTree<QString, QVector<Repetitor>> *subjectTree;  // Tree member variable

    void searchRepetitors();

private slots:
    void onSearchButtonClicked();
};

#endif // REPETITORSEARCHWIDGET_H
