#include "diylabel.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
Diylabel::Diylabel(const QString & text,QWidget* parent)
    :QLabel(parent)
{
     this->setText(text);
    QFont ft;
    ft.setPointSize(20);
    this->setFont(ft);

    this->adjustSize();

    this->setStyleSheet("border:2px solid red;");
}


void Diylabel::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"label";
    emit clicked();
}
