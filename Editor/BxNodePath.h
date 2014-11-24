#ifndef BXNODEPATH_H
#define BXNODEPATH_H

#include "BxNodePathPoint.h"
#include <QGraphicsScene>

class BxNodePath
{
public:
    BxNodePath(QGraphicsScene* );
    void writeToJson(QJsonObject &);
    void readFromJson(const QJsonObject &);
    void addPoint(const QPointF &);

private:
    QVector<BxNodePathPoint*> mPoints;
    QGraphicsScene* mScene;
};

#endif // BXNODEPATH_H
