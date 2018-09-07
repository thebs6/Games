#ifndef BOOKLIST_H
#define BOOKLIST_H

#include "diylabel.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QPushButton>
#include <QList>
#include <booklabel.h>

class BookList : public QWidget
{
    Q_OBJECT
public:
    explicit BookList(QWidget *parent = nullptr,QString sqlcom = "0",QString Sno = 0,bool Isadmin = false);
    void add(QWidget *widget);
    void remove();
    void FindaBook(QString BookName);
    void FindStuBook(QString Sname);
signals:

public slots:

private:
    QList<booklabel*> labellist;
    QVBoxLayout* m_pSCVLayout;
    QScrollArea* m_pChatListScrollArea;
    QWidget* widget = new QWidget(this);

    int j ;

    QString Sno_;
};

#endif // BOOKLIST_H
