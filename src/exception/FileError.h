#ifndef FILEERROR_H
#define FILEERROR_H

#include "ErrorBase.h"

class FileError : public ErrorBase {
public:
    explicit FileError(const QString &message, const QString &context = QString());
    void showError() const override; // Реализация для отображения через QMessageBox
};

#endif // FILEERROR_H
