#include "FileError.h"

FileError::FileError(const QString &message, const QString &context)
        : ErrorBase(message, context) {}

void FileError::showError() const {
    QString fullMessage = "File Error: " + message;
    if (!context.isEmpty()) {
        fullMessage += "\nContext: " + context;
    }
    QMessageBox::warning(nullptr, "File Error", fullMessage);
}
