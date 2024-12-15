#include "File.h"

File::File(const QString &filePath) : filePath(filePath) {}

bool File::openFile(QFile &file, QIODevice::OpenMode mode) const {
    file.setFileName(filePath);
    if (!file.open(mode)) {
        qDebug() << "Ошибка: Не удалось открыть файл" << filePath;
        return false;
    }
    return true;
}
