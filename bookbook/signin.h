#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <database.h>
#include <QMessageBox>
#include <QRegExp>
#include <QSqlQuery>
#include <QRegExpValidator>
#include <mainwin.h>
#include <booklabel.h>
class SignIn : public QWidget
{
    Q_OBJECT
public:
    explicit SignIn(QWidget *parent = nullptr);

signals:

public slots:
    void ButtonSol();
    bool AllowIn();
    void AddStu(QString Sid,QString Sname);
    bool IsAdmin();
private:
    QString uID;
    QString uPW;

    QLineEdit* id_;
    QLineEdit* pw_;

    QPushButton* go;


};

#endif // SIGNIN_H
