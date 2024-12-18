#include "TestFile.h"

#include <QTextStream>

TestFile::TestFile(const QString &filePath) : File(filePath) {
    listTest = new QList<Test>();
}

bool TestFile::load() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    listTest->clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|"); // Name rep|subj|date|time|filePath
        auto* newTest = new Test(parts[0], parts[1], QDate::fromString(parts[2], "dd.MM.yyyy"),
                                 QTime::fromString(parts[3], "HH:mm"), parts[4]);
        listTest->append(*newTest);
        qDebug() << listTest->back().getName() << "testfile";
    }

    file.close();
    return true;
}

bool TestFile::save() {
    QFile file(filePath);
    if (!openFile(file, QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    for (auto& test : *listTest) {
        out << test.getName() + "|" + test.getSubject() + "|" + test.getDate().toString("dd.MM.yyyy") + "|"
        + test.getTime().toString("HH:mm") + "|" + test.getTestFilePath() + "|" + "\n";
        qDebug() << "MOKFDSMKCOSD";
    }
    file.close();
    return true;
}

QList<Test> TestFile::getList() {
    return *listTest;
}
void TestFile::setList(QList<Test> &list) { listTest = &list; }