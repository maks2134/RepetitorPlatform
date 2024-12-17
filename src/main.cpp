#include <QApplication>
#include "auth/auth.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Auth authWidget;
    authWidget.show();
    return app.exec();
}

