#ifndef DIYLABEL_H
#define DIYLABEL_H

#include <QLabel>
#include <QString>
#include <QWidget>
#include <QMouseEvent>
class Diylabel:public QLabel
{
    Q_OBJECT
public:
    Diylabel(const QString &text,QWidget *parent=0);
    ~Diylabel(){}
signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // DIYLABEL_H
