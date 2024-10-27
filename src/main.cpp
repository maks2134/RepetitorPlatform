#include <QApplication>
#include <QPushButton>
#include "controllers/UserController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);

    UserController userController("data/users.txt");

    button.show();
    return QApplication::exec();
}
