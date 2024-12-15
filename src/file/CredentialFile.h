#ifndef CREDENTIALFILE_H
#define CREDENTIALFILE_H

#include "File.h"
#include <QMap>

class CredentialFile : public File {
private:
    QMap<QString, QString> credentials;

public:
    explicit CredentialFile(const QString &filePath);
    ~CredentialFile() override = default;

    const QMap<QString, QString> &getCredentials() const;

    bool load() override;
    bool save() override;

    void addCredential(const QString &login, const QString &hashedPassword);
};

#endif // CREDENTIALFILE_H
