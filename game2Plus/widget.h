#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "astar.h"
#include <QPushButton>
#include <QLabel>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Widget(QWidget *parent = 0);
    void MapInit();
    bool isSame(int row1,int col1,int row2,int col2);
    void pathLine();
    void Isleep(unsigned int msec);
    void GameWinShow();
    void timeStart();
    void GetRandMap();
    void GameStop();
    bool IsWin();
    ~Widget();


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    Ui::Widget *ui;
    int x = 0,y = 0;
    const int game_N = 13;
    QVector<QVector<int>> Map =
    {
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,4,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,2,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,3,3,4,0,0},
        { 0,0,0,2,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,2,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,2,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0},
        { 0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    QVector<QVector<int>> copyMap = Map;
    QPushButton StartGame;
    QPushButton GameTime;
    QPushButton Stop;
    int reX1,reY1,reX2,reY2;
    int temp;
    bool now = false;
    QList<Point *> PathL;
    int time0 ;
    int round = 0;
    bool StopFlag = false;
};

#endif // WIDGET_H
