#include "booklabel.h"

#include <QPushButton>
#include <QLabel>
#include <QDebug>
booklabel::booklabel(const QString & text,QWidget* parent,QString BookIsbn,bool Admin,QString Sno)
    :QLabel(parent)
{
    text_ = text;
    Sno_ = Sno;
    BookIsbn_ = BookIsbn;
    Admin_ = Admin;
     this->setText(text);
    QFont ft;
    ft.setPointSize(20);
    this->setFont(ft);

    this->adjustSize();

    this->setStyleSheet("border:2px solid red;");
}


void booklabel::mousePressEvent(QMouseEvent* event)
{

   widgetinit();
}
void booklabel::BorrowBook()
{

    QSqlQuery query;
    if(query.exec(QString("insert into sb (SBSno,SBISBN,SBtime,SBbacktime) value('%1','%2',now(),date_add(now(),interval 1 day));").arg(Sno_,BookIsbn_)))
    {
        if(query.exec(QString("update book set Bexist = Bexist-1 where ISBN = '%1'").arg(BookIsbn_)))
        qDebug()<<"ook";
    }
    else
    {
        qDebug()<<QString("insert into sb (SBSno,SBISBN,SBtime,SBbacktime) value('%1','%2',now(),date_add(now(),interval 1 day));").arg(Sno_,BookIsbn_);
    }
}

void booklabel::widgetinit()
{
    GetInfo();
    bookinfo = new QWidget;
    QPushButton* Borrow = new QPushButton("借",bookinfo);
    Borrow->hide();
    connect(Borrow,QPushButton::released,this,&BorrowBook);
    bookinfo->resize(800,100);
    if(!Admin_)  //学生看到的
    {
        Borrow->show();
        Borrow->move(bookinfo->width()/2 - 100,40);

        //借书判断够不够借
        if(infolist[7].toInt() > 0)
        {
            for(int i = 0; i < 8;i++)
            {
                QLabel* info = new QLabel(infolist[i],bookinfo);
                info->move(i*bookinfo->width()/9,20);
            }
            qDebug()<<infolist[7];
            bookinfo->show();
        }
        else
            Borrow->hide();
    }

}

void booklabel::GetInfo()   //记得清空list
{
    infolist.clear();
    QSqlQuery query;
    int i = 0;
    query.exec(QString("select * from book where ISBN = '%1'").arg(BookIsbn_));
    while(query.next())
    {
        while(i < 8)
        {
            infolist.push_back(query.value(i++).toString());

        }
    }
}

