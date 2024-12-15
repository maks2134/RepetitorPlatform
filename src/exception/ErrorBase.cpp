#include "ErrorBase.h"

ErrorBase::ErrorBase(const QString &message, const QString &context)
        : message(message), context(context) {}

QString ErrorBase::getMessage() const {
    return message;
}

QString ErrorBase::getContext() const {
    return context;
}
