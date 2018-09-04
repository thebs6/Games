#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QList>
#include <QTime>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    this->setFixedSize(1000,800);
    //GetRandMap();                          //开启随机地图模式
    StartGame.setParent(this);
    StartGame.move(600,600);
    StartGame.resize(250,150);
    StartGame.setText("Start Game");
    GameTime.move(900,0);
    GameTime.resize(100,50);
    GameTime.setParent(this);
    GameTime.hide();
    Stop.setText("暂停");
    Stop.move(800,0);
    Stop.setParent(this);
    Stop.resize(100,50);
    Stop.hide();
    connect(&StartGame,&QPushButton::released,this,&GameWinShow);
    connect(&Stop,&QPushButton::released,this,&GameStop);

}

void Widget::timerEvent(QTimerEvent *event)
{
    static int time = 100;
    GameTime.setText(QString("time: %1 s").arg(time));
    if(time > 0 && !StopFlag) time--;
    else if(time < 0 )
    {
        time = 100;
        qDebug() << "Game Over!";

        if(QMessageBox::information(NULL,"Game Over","游戏结束","重新开始","退出") == 0)
        {
            GetRandMap();
            round = 0;
        }
        else
        {
            this->close();
        }
    }

}

void Widget::timeStart()
{
    this->time0 = this->startTimer(1000);

}


void Widget::GameWinShow()
{
    now = true;
    StartGame.hide();
    GameTime.show();
    Stop.show();
    timeStart();
    update();
}

void Widget::GameStop()
{
    StopFlag = true;
    if(QMessageBox::information(NULL,"Pause","游戏暂停","继续") == 0)
        StopFlag = false;
    else
        StopFlag = true;
}

void Widget::Isleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


Widget::~Widget()
{
    delete ui;
}

bool Widget::isSame(int row1,int col1,int row2,int col2)
{
    if(Map[row1][col1] == Map[row2][col2])return true;
    else return false;
}
void Widget::pathLine()
{
    for(int i = 1;i < PathL.size() - 1;i++)
    {
        if(PathL[i] -> x == PathL[i-1]->x && PathL[i] -> x == PathL[i+1]->x)
        Map[PathL[i] -> x][PathL[i]->y] = 51; //横
        else if(PathL[i] -> y == PathL[i-1]->y && PathL[i] -> y == PathL[i+1]->y)
        Map[PathL[i] -> x][PathL[i]->y] = 52; //竖
        else if(PathL[i] -> x-1 == PathL[i-1]->x && PathL[i] -> y == PathL[i-1]->y
              &&PathL[i] -> x == PathL[i+1]->x && PathL[i]->y-1 == PathL[i+1]->y
              ||PathL[i] -> x-1 == PathL[i+1]->x && PathL[i] -> y == PathL[i+1]->y
             &&PathL[i] -> x == PathL[i-1]->x && PathL[i]->y-1 == PathL[i-1]->y)
               Map[PathL[i] -> x][PathL[i]->y] = 53; //左上
        else if(PathL[i] -> x-1 == PathL[i-1]->x && PathL[i] -> y == PathL[i-1]->y
              &&PathL[i] -> x == PathL[i+1]->x && PathL[i]->y+1 == PathL[i+1]->y
              ||PathL[i] -> x-1 == PathL[i+1]->x && PathL[i] -> y == PathL[i+1]->y
             &&PathL[i] -> x == PathL[i-1]->x && PathL[i]->y+1 == PathL[i-1]->y)
               Map[PathL[i] -> x][PathL[i]->y] = 54; //右上
        else if(PathL[i] -> x+1 == PathL[i-1]->x && PathL[i] -> y == PathL[i-1]->y
              &&PathL[i] -> x == PathL[i+1]->x && PathL[i]->y-1 == PathL[i+1]->y
              ||PathL[i] -> x+1 == PathL[i+1]->x && PathL[i] -> y == PathL[i+1]->y
             &&PathL[i] -> x == PathL[i-1]->x && PathL[i]->y-1 == PathL[i-1]->y)
               Map[PathL[i] -> x][PathL[i]->y] = 55; //左下
        else if(PathL[i] -> x+1 == PathL[i-1]->x && PathL[i] -> y == PathL[i-1]->y
              &&PathL[i] -> x == PathL[i+1]->x && PathL[i]->y+1 == PathL[i+1]->y
              ||PathL[i] -> x+1 == PathL[i+1]->x && PathL[i] -> y == PathL[i+1]->y
             &&PathL[i] -> x == PathL[i-1]->x && PathL[i]->y+1 == PathL[i-1]->y)
               Map[PathL[i] -> x][PathL[i]->y] = 56; //右下

    }
    update();
    Isleep(200);
    for(auto linePoint : PathL)
    {
        Map[linePoint->x][linePoint->y] = 0;
        update();

    }
}
void Widget::paintEvent(QPaintEvent *event)
{
    qDebug() <<"1";
    QPainter p(this);
    QPainter back(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    if(now)
    {

        back.drawPixmap(0,0,width(),height(),QPixmap(":image/aa.jpg"));
//        for(int x = 0;x < width();x += width()/game_N)
//            for(int y = 0;y < height(); y += height()/game_N)
//            {
//                p.drawLine(x,y,width(),y);
//                p.drawLine(x,y,x,height());
//            }
        for(x = 0; x < game_N;x++)

        {
            for(y = 0;y < game_N ;y++)
            {
                QString imageName = QString(":image/%1.png").arg(Map[x][y]);
                p.drawPixmap(y+y*width()/game_N,x+x*height()/game_N,width()/game_N,height()/game_N,imageName);
            }
        }
    }
    else
    {
        back.drawPixmap(0,0,width(),height(),QPixmap(":image/back.png"));
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    int temp = 0;
    Astar test;
    test.gameMap(Map);
    Point p1(reX1,reY1);
    Point p2(reX2,reY2);
    int x = event->x();
    int y = event->y();
    int Map_Y = x/(width()/game_N);
    int Map_X = y/(height()/game_N);
    if(round == 1)
    {
        reX2 = Map_X;
        reY2 = Map_Y;
        p2.x = reX2;
        p2.y = reY2;
        round = 0;

        if(isSame(p1.x,p1.y,p2.x,p2.y))
        {
            temp = Map[p1.x][p1.y];
            Map[p1.x][p1.y] = 0;
            Map[p2.x][p2.y] = 0;
            test.gameMap(Map);
            Point *result = test.FindPath(&p1,&p2);
//            qDebug()<< p1.x<<" "<<p1.y<<endl;
//            qDebug()<< p2.x<<" "<<p2.y<<endl;
            QList<Point *>path;
            while(result)
            {
                path.push_front(result);
                result = result->parent;
            }

            if(!path.isEmpty())
            {
                path.push_back(&p2);
                qDebug()<<"right";
                PathL = path;
                for(auto p:path)
                {
                    qDebug()<< p->x<<" "<<p->y<<endl;
                }
                pathLine();
                PathL.clear();

//                Map[reX1][reY1] = 0;
//                Map[reX2][reY2] = temp;
                if(IsWin())
                {
                      if(QMessageBox::information(NULL,"游戏结束","You Win!","再来一局","退出") == 0)
                      {
                          GetRandMap();
                      }
                      else
                      {
                          this->close();
                      }
                }


                update();
            }
            else
            {
                Map[p1.x][p1.y] = temp;
                Map[p2.x][p2.y] = temp;
                test.gameMap(Map);
            }
        }
    }
    else if(round == 0)
    {
        reX1 = Map_X;
        reY1 = Map_Y;
        qDebug()<<"rex= "<<reX1<<"rey="<<reY1<<endl;
//        p1.x = reX1;
//        p1.y = reY1;
        round = 1;
    }
}

bool Widget::IsWin()
{
    for(x = 0; x < game_N;x++)

    {
        for(y = 0;y < game_N ;y++)
        {
            if(Map[x][y] != 0 )
                return false;
        }
    }
    return true;
}
void Widget::GetRandMap()
{
    QVector<QVector<int>> RandMap;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int x = 1; x < game_N-1;x++)
    {
        for(int y = 1;y < game_N-1 ;y++)
        {
            Map[x][y] = qrand()%(13-1);
        }
    }
}
//    qDebug()<<"round="<<round<<"rex1 = " <<reX1<< "rey1="<<reY1<<"rex2= "<<reX2<<"rey2="<<reY2;
//    if(Map[Map_X][Map_Y] != 0)
//    {
//        p.drawPixmap(Map_Y+Map_Y*width()/game_N,Map_X+Map_X*height()/game_N,width()/game_N,height()/game_N,);
//    }
//}
