#include "signin.h"

SignIn::SignIn(QWidget *parent) : QWidget(parent)
{
    this->resize(400,400);
    id_ = new QLineEdit(this);
    id_->move(150,150);
    pw_ = new QLineEdit(this);
    pw_->move(150,200);
    go = new QPushButton("登陆",this);
    go->move(100,240);
    booklabel *test = new booklabel("1234",this,"1234",false);
    test->move(200,0);
    test->setText("2222");
    connect(go,QPushButton::released,this,&ButtonSol);
}

bool SignIn::AllowIn()
{

    QSqlQuery query;
    query.exec(QString("select * from stu where Sno = '%1'").arg(uID));
    if(query.next())return true;
    else
    {
        return false;
    }


}

bool SignIn::IsAdmin()
{
    QSqlQuery query;
    query.exec(QString("select Apswd from admin where Ano = '%1'").arg(uID));
    qDebug()<<QString("select Apswd from admin where Ano = '%1'").arg(uID);
    if(query.next())
    {
        query.value(0) == uPW;
        return true;
    }
    else return false;
}

void SignIn::AddStu(QString Sid,QString Sname)
{
   QSqlQuery query;
   if(query.exec(QString("insert into stu(Sno,Sname) VALUES('%1','%2');").arg(Sid,Sname)))
       qDebug()<<"insert successful";
   else qDebug()<<"insert falue";
}
void SignIn::ButtonSol()
{


    QString pa = "3[1-2]1[0-9]0[0-9]{5}";
    QRegExp* rx;
    rx = new QRegExp(pa);
    uID = id_->text();
    uPW = pw_->text();
    if(rx->exactMatch(uID))
    {
        if(AllowIn())qDebug()<<"yes";
        else
        {
            AddStu(uID,"afu");
        }
        MainWin* mainwin = new MainWin(NULL,uID,false);
        mainwin->show();
        this->hide();


    }
    else if(!uPW.isEmpty())
    {
         if(IsAdmin())
         {
             MainWin* adminwin = new MainWin(NULL,uID,true);
             this->hide();
             adminwin->show();
         }
         else qDebug()<<"u are not admin";

    }
}
