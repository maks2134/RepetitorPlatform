    #ifndef ERRORBASE_H
    #define ERRORBASE_H

    #include <QString>
    #include <QMessageBox>
    #include <QDebug>

    class ErrorBase {
    protected:
        QString message; // Описание ошибки
        QString context; // Контекст ошибки

    public:
        ErrorBase(const QString &message, const QString &context = QString());
        virtual ~ErrorBase() = default;

        virtual void showError() const = 0; // Абстрактный метод для отображения ошибки
        QString getMessage() const;
        QString getContext() const;
    };

    #endif // ERRORBASE_H
