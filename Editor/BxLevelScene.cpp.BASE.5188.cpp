#include "BxLevelScene.h"
#include <QGraphicsSceneMouseEvent>

#include "BxActorItem.h"

BxLevelScene::BxLevelScene()
{
    mMode = moveItem;
}


void BxLevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() != Qt::LeftButton)
        return;

    switch (mMode)
    {
        case insertItem:
        {
            BxActorItem* newItem = new BxActorItem((QRect(-50, -50, 100, 100)));

            BxIntAttribute* radiusAttr = new BxIntAttribute("radius", 5);
            newItem->addAttribute(radiusAttr);


            newItem->setPos(event->scenePos());
            addItem(newItem);

            emit(itemInserted(newItem));
            setMode(moveItem);
        }
            break;
        default:
            ;
    }
    QGraphicsScene::mousePressEvent(event);
}

void BxLevelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}
