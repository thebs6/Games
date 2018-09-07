#ifndef BOOKLABEL_H
#define BOOKLABEL_H


#include <QLabel>
#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <database.h>
#include <QList>
class booklabel:public QLabel
{
    Q_OBJECT
public:
    booklabel(const QString &text,QWidget *parent=0,const QString BookIsbn = NULL,bool Admin = false,QString Sno = NULL);
    void widgetinit();
    void GetInfo();
    void BorrowBook();
    ~booklabel(){}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
private:
    QString text_;
    QString BookIsbn_;
    QString Sno_;
    bool Admin_;
    QWidget *bookinfo;

    QList<QString> infolist;
};

#endif // BOOKLABEL_H
