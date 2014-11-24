#include "BxLevelScene.h"
#include <QGraphicsSceneMouseEvent>

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
            BxActorItem* newItem = new BxActorItem();

            BxIntAttribute* radiusAttr = new BxIntAttribute("radius", 5);
            newItem->addAttribute(radiusAttr);


            newItem->setPos(event->scenePos());
            insertActor(newItem);
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

void BxLevelScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Backspace ||
       event->key() == Qt::Key_Escape )
    {
        QList<QGraphicsItem*>items = this->selectedItems();
        foreach(auto i, items)
        {
            BxActorItem* actor = dynamic_cast<BxActorItem*>(i);
            if(actor)
            {
                removeItem(actor);
            }
        }
    }
}

void BxLevelScene::insertActor(BxActorItem* in)
{
    addItem(in);
    emit(itemInserted(in));
}
