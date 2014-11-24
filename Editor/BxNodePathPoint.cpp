#include "BxNodePathPoint.h"
#include "QGraphicsScene"

BxNodePathPoint::BxNodePathPoint(QGraphicsItem* parent, QGraphicsScene* scene) :
    QGraphicsEllipseItem(QRect(-5, -5, 10, 10), parent)
{
    mScene = scene;
    initialise();
}

void BxNodePathPoint::writeToJson(QJsonObject& JsonPos)
{
    JsonPos["x"]=x();
    JsonPos["y"]=y();
}

void BxNodePathPoint::initialise()
{
    setFlag(ItemIsMovable, true);
    setFlag(ItemIsSelectable, true);
    setFlag(ItemSendsGeometryChanges);
}

QVariant BxNodePathPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionHasChanged)
    {
        foreach(BxNodeLine* line, mConnections)
        {
            line->adjust();
//            line->update();
        }
#warning this is inefficient
    //mScene->update();
    }
    return QGraphicsItem::itemChange(change, value);
}
