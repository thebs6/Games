#ifndef ASTAR_H
#define ASTAR_H
#include <QList>
#include <QVector>
struct Point
{
    int x,y;
    int F,G,H;
    Point *parent;
    Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL){}
};

class Astar
{
public:
    void MapInit(QVector<QVector<int>> &Map);
    int getF(const Point *s, const Point *t,const Point *e);
    int getG(const Point *s,const Point *p);
    int getH(const Point *p,const Point *e);
    void test(Point *s,  Point *t,const Point *e);
    bool isUsePoint(const Point *t,const Point *p);
    bool Inlist(const Point* t,QList<Point *>list);
    Point* FindPath(const Point *start,const Point *end);
    Point* IsMin();
    void gameMap(QVector<QVector<int>> &map);
    QVector<Point*> getSurround(const Point *p);

private:
    QVector<QVector<int>> testMap;
    QList<Point *>Open;
    QList<Point *>Close;
    //QList<Point *>result;
};


#endif // ASTAR_H
