#include "account.h"
#include "ui_account.h"
#include <QMessageBox>

account::account(QWidget *parent) :
        BaseWin(parent),
        ui(new Ui::account) {
    ui->setupUi(this);
    loadRepetitorsFromFile(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");

    connect(ui->pushButton_2, &QPushButton::clicked, this, &account::onDeleteButtonClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &account::onReturnButtonClicked);
}


account::~account() {
    delete ui;
}

void account::displayAllRepetitors() {
    ui->listWidget->clear();

    for (auto it = subjectRepetitors.begin(); it != subjectRepetitors.end(); ++it) {
        const QString &subject = it.key();
        const QVector<QString> &repetitors = it.value();

        for (const QString &fullData : repetitors) {
            QStringList dataParts = fullData.split("||");
            QString name = dataParts.value(0).trimmed();
            QString date = dataParts.value(1).trimmed();
            QString filePath = dataParts.value(2).trimmed();

            // Формат вывода: Имя (Предмет, Дата)
            QString displayText = QString("%1 (%2, %3)").arg(name, subject, date);

            QListWidgetItem *item = new QListWidgetItem(displayText, ui->listWidget);
            item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, fullData); // Сохраняем полные данные
        }
    }
}

void account::onDeleteButtonClicked() {
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "No repetitors selected for deletion.");
        return;
    }

    for (QListWidgetItem *item : selectedItems) {
        QString fullDataToDelete = item->data(Qt::UserRole).toString();  // Получаем полные данные

        // Разделяем данные на части: Имя, Дата, Путь
        QStringList dataParts = fullDataToDelete.split("||");
        if (dataParts.size() < 3) {
            continue; // Если данные некорректные, пропускаем
        }

        QString nameToDelete = dataParts[0].trimmed();
        QString date = dataParts[1].trimmed();
        QString filePath = dataParts[2].trimmed();

        // Определяем предмет, из которого удаляется репетитор
        QString subject;
        for (auto it = subjectRepetitors.begin(); it != subjectRepetitors.end(); ++it) {
            const QVector<QString> &repetitors = it.value();
            for (const QString &repetitor : repetitors) {
                if (repetitor.startsWith(nameToDelete + "||")) {
                    subject = it.key();
                    break;
                }
            }
            if (!subject.isEmpty()) {
                break;
            }
        }

        if (!subject.isEmpty()) {
            // Удаляем репетитора из данных
            QVector<QString> &repetitors = subjectRepetitors[subject];
            repetitors.removeAll(fullDataToDelete);  // Удаляем репетитора

            if (repetitors.isEmpty()) {
                subjectRepetitors.remove(subject);  // Удаляем предмет, если он пустой
            }

            delete item;  // Удаляем элемент из интерфейса
        } else {
            QMessageBox::warning(this, "Error", "Repetitor not found.");
        }
    }

    saveRepetitorsToFile(R"(C:\pnya\RepetitorPlatform\src\data\test.txt)");  // Сохраняем изменения
    QMessageBox::information(this, "Deleted", "Selected repetitors have been deleted.");
}



void account::onReturnButtonClicked() {
    mainWin *mainWindow = new mainWin;
    mainWindow->show();
    this->close();
}

void account::saveRepetitorsToFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing:" << fileName;
        return;
    }

    QTextStream out(&file);

    // Перезаписываем все данные
    for (auto it = subjectRepetitors.begin(); it != subjectRepetitors.end(); ++it) {
        const QString &subject = it.key();
        const QVector<QString> &repetitors = it.value();

        for (const QString &repetitor : repetitors) {
            // Разделяем на части, чтобы сохранить в правильном формате
            QStringList parts = repetitor.split("||");
            if (parts.size() == 3) {
                QString name = parts[0].trimmed();
                QString date = parts[1].trimmed();
                QString filePath = parts[2].trimmed();

                // Сохраняем в формате: Имя|Предмет|Дата||Путь к файлу
                out << name << "|" << subject << "|" << date << "||" << filePath << "\n";
            }
        }
    }

    file.close();
    qDebug() << "File saved successfully:" << fileName;
}




void account::loadRepetitorsFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << fileName;
        return;
    }

    subjectRepetitors.clear(); // Очищаем текущие данные

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");

        if (parts.size() >= 5) { // Проверяем, чтобы было как минимум 5 частей
            QString name = parts[0].trimmed();      // Имя репетитора
            QString subject = parts[1].trimmed();  // Предмет
            QString date = parts[2].trimmed();     // Дата
            QString filePath = parts[4].trimmed(); // Путь к файлу

            // Объединяем все данные в строку и сохраняем их
            QString fullData = QString("%1||%2||%3").arg(name, date, filePath);
            subjectRepetitors[subject].append(fullData);
        }
    }

    file.close();
    displayAllRepetitors(); // Отображаем всех репетиторов
}


