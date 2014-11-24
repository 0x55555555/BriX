#ifndef BXNODEPATHPOINT_H
#define BXNODEPATHPOINT_H

#include <QJsonObject>
#include <QGraphicsEllipseItem>
#include <BxNodeLine.h>

class BxNodeLine;

class BxNodePathPoint : public QGraphicsEllipseItem
{
public:
    BxNodePathPoint(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    void initialise();
    void writeToJson(QJsonObject &);
    //void upstreamPointPosChanged(const QPointF &);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


//private:
    QVector<BxNodeLine*> mConnections;
private:
    QGraphicsScene* mScene;
};

#endif // BXNODEPATHPOINT_H
