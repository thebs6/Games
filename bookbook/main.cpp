
#include <QApplication>
#include "mainwin.h"
#include "booklist.h"
#include "database.h"
#include <signin.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    database *con = new database;
    SignIn w;
    w.show();

    return a.exec();
}

