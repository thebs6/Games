#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

class database
{
public:
    database();
    ~database(){}
    void ConnectDataBase();
};

#endif // DATABASE_H
