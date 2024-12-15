#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDebug>

class File {
protected:
    QString filePath;

public:
    explicit File(const QString &filePath);
    virtual ~File() = default;

    bool openFile(QFile &file, QIODevice::OpenMode mode) const;

    virtual bool load() = 0;  // Абстрактный метод для загрузки
    virtual bool save() = 0;  // Абстрактный метод для сохранения
};

#endif // FILE_H
