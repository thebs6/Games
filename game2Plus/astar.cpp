#include <astar.h>
#include "qmath.h"
#include <QDebug>

void Astar::gameMap(QVector<QVector<int>> &map)
{
    testMap = map;
}
int Astar::getH(const Point *p,const Point *e)
{
    return (abs(p->x-e->x)+abs(p->y-e->y));
}

int Astar::getG(const Point *s,const Point *p)
{
    return (abs(p->x-s->x)+abs(p->y-s->y));
}

int Astar::getF(const Point *s, const Point *t,const Point *e)
{
    int F = (getG(s,t))+(getH(t,e));
    return (F);
}

bool Astar::Inlist(const Point* t,QList<Point *>list)
{
    for(auto p :list )
    {
        if(t->x == p->x && t->y == p->y)
            return true;
    }
    return false;
}
bool Astar::isUsePoint(const Point *t,const Point *p)
{
    if((t->x == p->x && t->y == p->y) || (t->x < 0) || t->x > testMap.size() ||
        t->x < 0 || t->y > testMap[0].size() || t->y < 0 || testMap[t->x][t->y] != 0
          ||Inlist(t,Close)  )
        return false;
    else
    {
        if(abs(t->x-p->x)+(t->y-p->y) == 1)
        return true;
        else
        {
            if(testMap[t->x][p->y] == 0 && testMap[t->x][p->y] == 0)
                return true;
            else return false;
        }
    }
}
QVector<Point*> Astar::getSurround(const Point *p)
{
    QVector<Point *>SurPoint;
//    for(int x = p->x-1;x <= p->x+1 && x < testMap.size();x++)
//        for(int y = p->y-1;y <= p->y+1 && y < testMap[0].size();y++)
//            if(isUsePoint(new Point(x,y),p))
//            {
//                SurPoint.push_back(new Point(x,y));  //没加new
//            }
    for(int x = p->x-1;x <= p->x+1 && x < testMap.size();x++)
        if(isUsePoint(new Point(x,p->y) , p))
        {
            SurPoint.push_back(new Point(x,p->y));
        }
    for(int y = p->y-1;y <= p->y+1 && y < testMap[0].size();y++)
        if(isUsePoint(new Point(p->x,y) , p))
        {
            SurPoint.push_back(new Point(p->x,y));
        }

    return SurPoint;
}
void Astar::test( Point *s,  Point *t,const Point *e)
{
    int F,G,H;
    G = getG(s,t);
    H = getH(t,e);
    F = getF(s,t,e);
    t->G = G;
    t->F = F;
    t->H = H;
    qDebug()<< t->F <<t->G<<t->H;
}

Point* Astar::IsMin()
{
    auto MinPoint = Open.constFirst();
    for(auto &P : Open)
    {
        if(P->F < MinPoint->F)
            MinPoint = P;
    }
    //qDebug()<<MinPoint->x<<MinPoint->y << MinPoint->F;
    return MinPoint;
}
Point* Astar::FindPath(const Point *start,const Point *end)
{
    Open.push_back(new Point(start->x,start->y));
    while(!Open.isEmpty())
    {
        auto curPoint = IsMin();
        Open.removeOne(curPoint);
        Close.push_back(curPoint);
        auto surPoint = getSurround(curPoint);
        for(auto &sPoint : surPoint)
        {
            if(!Inlist(sPoint,Open))
            {
                sPoint -> parent = curPoint;
                sPoint -> G = getG(start,sPoint);
                sPoint -> H = getH(sPoint ,end);
                sPoint -> F = getF(start,sPoint,end);
                Open.push_back(sPoint);
            }
            else
            {
                int tempG = getG(curPoint, sPoint);
                if (tempG<sPoint->G)
                {
                    sPoint->parent = curPoint;

                    sPoint->G = tempG;
                    sPoint->F = getF(start,sPoint,end);
                }
            }

            if(Inlist(end,Open))
            {
                return curPoint;
            }
        }


    }
}

