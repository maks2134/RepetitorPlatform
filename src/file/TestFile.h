#ifndef CALENDARFILE_H
#define CALENDARFILE_H

#include "File.h"
#include <QMap>
#include <QDate>
#include "../test/Test.h"

class TestFile : public File {
private:
    QList<Test>* listTest;
public:
    TestFile(const QString &filePath);
    ~TestFile() override = default;

    QList<Test> getList();

    bool load() override;
    bool save() override;

    void setList(QList<Test> &list);
};

#endif // CALENDARFILE_H
