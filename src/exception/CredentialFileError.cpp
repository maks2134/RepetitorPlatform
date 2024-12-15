#include "CredentialFileError.h"

CredentialFileError::CredentialFileError(const QString &message, const QString &context)
        : FileError(message, context) {}

void CredentialFileError::showError() const {
    QString fullMessage = "Credential File Error: " + message;
    if (!context.isEmpty()) {
        fullMessage += "\nContext: " + context;
    }
    QMessageBox::critical(nullptr, "Credential File Error", fullMessage);
}
