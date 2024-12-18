#include "RepetitorSearchWidget.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>

RepetitorSearchWidget::RepetitorSearchWidget(QWidget *parent) : QWidget(parent) {
    // Инициализация элементов интерфейса
    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    repetitorListWidget = new QListWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(searchLineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(repetitorListWidget);

    connect(searchButton, &QPushButton::clicked, this, &RepetitorSearchWidget::onSearchButtonClicked);
}

void RepetitorSearchWidget::onSearchButtonClicked() {
    searchRepetitors();
}

void RepetitorSearchWidget::searchRepetitors() {
    QString subject = searchLineEdit->text();
    repetitorListWidget->clear();  // Очищаем список перед отображением новых результатов

    if (subjectTree->contains(subject)) {
        auto repetitors = subjectTree->operator[](subject);  // Use operator[] to get the value
        for (const auto &repetitor : repetitors) {
            auto* item = new QListWidgetItem(repetitor.getName());
            //item->setData(Qt::UserRole, repetitor.getTestFilePath()); // Save the file path
            repetitorListWidget->addItem(item);
        }
    } else {
        QMessageBox::information(this, "Search Result", "No repetitors found for this subject.");
    }
}

void RepetitorSearchWidget::setSubjectTree(BinarySearchTree<QString, QVector<Repetitor>> *tree) {
    subjectTree = tree;  // Set the subjectTree to the one passed from the parent
}
