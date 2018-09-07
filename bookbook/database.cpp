#include "database.h"

database::database()
{
    ConnectDataBase();
}

void database::ConnectDataBase()
{
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QMYSQL");
    db2.setHostName("localhost");
    db2.setUserName("root");
    db2.setPassword("er2wqar");
    db2.setDatabaseName("library_test");
    //连接失败
    if(!db2.open())
    {
        QMessageBox::warning(NULL,"错误",db2.lastError().text());
    }
}
