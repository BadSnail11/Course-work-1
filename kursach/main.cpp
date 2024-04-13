#include "mainwindow.h"
#include "authwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AuthWindow auth;
    QObject::connect(&auth, &AuthWindow::authClosed, &w, &MainWindow::on_auth_closed);
    w.show();
    auth.setModal(true);
    auth.exec();
    return a.exec();
}
