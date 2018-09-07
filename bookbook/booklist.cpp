#include "booklist.h"

BookList::BookList(QWidget *parent,QString sqlcom,QString Sno,bool Isadmin) : QWidget(parent)
{

    QSqlQuery query;
    Sno_ = Sno;


    this->m_pChatListScrollArea = new QScrollArea(this);
        this->m_pChatListScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        this->m_pChatListScrollArea->setWidgetResizable(true);

        this->m_pSCVLayout = new QVBoxLayout(this);
        this->m_pSCVLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);


        widget->setMinimumSize(72, 32);
        widget->setMaximumSize(80,32);






        query.exec(sqlcom);
        qDebug() <<sqlcom;
        while(query.next())
        {
            booklabel* book = new booklabel(
                        "书名：<<"+query.value(1).toString()+">>"+"    "+""
                        "作者："+query.value(2).toString(),widget,query.value(0).toString(),false,Sno_);
            labellist.push_back(book);
            book->setMinimumSize(book->size());
            qDebug()<<query.value(0).toString()+query.value(1).toString();
            this->m_pSCVLayout->addWidget(book);
        }

//        for (int i=0; i<j; ++i)
//        {
//            pushButton = new Diylabel(str.arg(i+1), widget);
//            pushButton->setMinimumSize(pushButton->size());
//            this->m_pSCVLayout->addWidget(pushButton);
//        }
        widget->setLayout(this->m_pSCVLayout);
        this->m_pChatListScrollArea->setWidget(widget);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
            mainLayout->addWidget(this->m_pChatListScrollArea);
            this->setLayout(mainLayout);
}

void BookList::add(QWidget *widget)
{
    this->m_pSCVLayout->addWidget(widget);
    qDebug() <<this->m_pSCVLayout->count();
}

void BookList::remove()
{
    qDebug() <<this->m_pSCVLayout->count();


        if(!labellist.isEmpty())
        {
            for(booklabel*item:labellist)
            {
                qDebug()<<item->text();
                delete item;
                labellist.removeOne(item);
            }
        }
        if(labellist.isEmpty())qDebug()<<"qq2q";

}

void BookList::FindaBook(QString BookName)
{
    QSqlQuery query2;
    query2.exec(QString("select * from book where Bname = '%1'").arg(BookName));
    qDebug()<<QString("select * from book where Bname = '%1'").arg(BookName);

    while(query2.next())
    {
        booklabel* book = new booklabel("书名：<<"+query2.value(1).toString()+">>"+"    "+""
                                      "作者："+query2.value(2).toString(),widget);
        labellist.push_back(book);
        book->resize(100,200);


        add(book);
    }
}

void BookList::FindStuBook(QString Sname)
{

    QSqlQuery query2;

    if(Sname == "all")
    {
        query2.exec(QString("select Sname,ISBN,Bname,SBtime,SBbacktime "
                             "from book,Sb,Stu "
                             "where ISBN = SBISBN and SBsno = Sno"));
    }
    else
    {
        query2.exec(QString("select Sname,ISBN,Bname,SBtime,SBbacktime"
                           " from book,Sb,Stu "
                           "where ISBN = SBISBN and SBsno = Sno and Sname = '%1';").arg(Sname));
    }
    while(query2.next())
    {
        booklabel* Stu = new booklabel("学生："+query2.value(0).toString()+"    "
                                      +"ISBN:"+query2.value(1).toString()+"    "
                                     +"书名："+query2.value(2).toString()
                                     +"借书时间："+query2.value(3).toString()+"    "
                                     +"还书时间："+query2.value(4).toString(),widget,query2.value(0).toString(),true);
        labellist.push_back(Stu);
        Stu->resize(100,200);


        add(Stu);
    }
}
