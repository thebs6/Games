#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent,QString uid,bool admin) :
    QWidget(parent),
    ui(new Ui::MainWin)
{
    UserId = uid;
    ui->setupUi(this);
    SqlCommon = "select * from book";
    sqlCommon2 = QString("select * from book,Sb,Stu where ISBN = SBISBN and SBsno = Sno and Sno = '%1';").arg(uid);

    booklist = new BookList(this,SqlCommon,UserId);
    qDebug()<<UserId;
    qDebug()<<SqlCommon;
    booklist->resize(600,200);
    booklist->move(0,150);




    if(!admin) //学生
    {
        StuWin();
    }
    else if(admin)
    {
         AdminWin();

    }


    TextLineSet();
    ButtonSet();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::TextLineSet()
{
    Abook =new QLineEdit(this);
    //Abook->move(200,150);
    Abook->setPlaceholderText("请输入你想要查找的书名...");
    Abook->show();

}

void MainWin::ButtonSet()
{
    Go = new QPushButton("查找",this);
    Del = new QPushButton("del",this);
    refresh = new QPushButton("刷新",this);
    refresh->move(500,100);
    Del->move(400,0);
    Go->move(300,0);

    connect(Del,QPushButton::released,this,&remove_);
    connect(Go,QPushButton::released,this,&RefreshList);
    connect(refresh,QPushButton::released,this,&RefreshStuwin);


}

void MainWin::remove_()
{
    booklist->remove();
}
void MainWin::RefreshList()
{

    SqlCommon = Abook->text();
    booklist->remove();

    booklist->FindaBook(SqlCommon);

}
void MainWin::RefreshStuwin()
{
    HaveBook->remove();
    //StuWin();
}
void MainWin::StuWin()
{

    QLabel *test = new QLabel(UserId,this);
    test->move(300,50);
    HaveBook = new BookList(this,sqlCommon2,UserId);
    HaveBook->resize(600,200);
    HaveBook->move(600,150);
}

void MainWin::AdminWin()
{
//    sqlCommon3 = QString("select ISBN,Bname,SBtime,SBbacktime "
//                         "from book,Sb,Stu "
//                         "where ISBN = SBISBN and SBsno = Sno ;");
    u_stubook = new BookList(this,NULL,UserId,true);
    u_stubook->FindStuBook(QString("all"));
    u_stubook->resize(600,200);
    u_stubook->move(600,150);


    Go2 = new QPushButton("差",this);
    Go2->move(450,100);
    connect(Go2,QPushButton::released,this,&AdminFStu);
    u_stubooklist = new QLineEdit(this);
    u_stubooklist->move(400,100);




    QLabel *test = new QLabel(UserId,this);
    test->move(300,50);


}

void MainWin::AdminFStu()
{
    u_stubook->remove();
    u_StuName = u_stubooklist->text();
    if(!u_StuName.isEmpty())
    {
        u_stubook->FindStuBook(u_StuName);
        qDebug()<<u_StuName;
    }

}

