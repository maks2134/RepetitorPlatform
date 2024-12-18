 #ifndef QUESTIONFILE_H
#define QUESTIONFILE_H

#include "File.h"
#include <QStringList>

class QuestionFile : public File {
private:
    QStringList questions;
    QStringList correctAnswers;

public:
    explicit QuestionFile(const QString &filePath);
    ~QuestionFile() override = default;

    const QStringList &getQuestions() const;
    const QStringList &getCorrectAnswers() const;

    bool load() override;
    bool save() override;

    void addQuestion(const QString &question, const QString &answer);
};

#endif // QUESTIONFILE_H
