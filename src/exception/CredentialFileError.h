#ifndef CREDENTIALFILEERROR_H
#define CREDENTIALFILEERROR_H

#include "FileError.h"

class CredentialFileError : public FileError {
public:
    explicit CredentialFileError(const QString &message, const QString &context = QString());
    void showError() const override;
    static CredentialFileError fileOpenError(const QString &fileName) {
        return CredentialFileError("Не удалось открыть файл.", fileName);
    }
};

#endif // CREDENTIALFILEERROR_H
