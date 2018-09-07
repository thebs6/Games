#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <booklist.h>
#include <QDebug>
#include <diylabel.h>

namespace Ui {
class MainWin;
}

class MainWin : public QWidget
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0,QString uid = 0,bool admin = 0);
    void TextLineSet();
    void ButtonSet();
    void RefreshList();
    void remove_();
    void StuWin();
    void AdminWin();
    void AdminFStu();
    void RefreshStuwin();
    ~MainWin();
private:
    Ui::MainWin *ui;
    QString SqlCommon,sqlCommon2,sqlCommon3;
    QString UserId;
        QString u_StuName;

    BookList* booklist;
    BookList* HaveBook;

    BookList* u_stubook;  //某个学生借了什么书
    QPushButton* Go;
    QPushButton* Del;
    QPushButton* Go2;
    QPushButton* refresh;


    QLineEdit* Abook;
    QLineEdit* u_stubooklist;  //查询借书学生姓名输入框
};

#endif // MAINWIN_H
