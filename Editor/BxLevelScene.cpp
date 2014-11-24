#include "BxLevelScene.h"
#include <QGraphicsSceneMouseEvent>

BxLevelScene::BxLevelScene()
{
    mMode = moveItem;
    mCameraPath = new BxNodePath(this);
}


void BxLevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() != Qt::LeftButton)
        return;

    switch (mMode)
    {
        case insertItem:
        {
            // CONSTRUCT ARBITRARY ACTOR:
            BxNodeActor* newItem = new BxNodeActor();
            BxIntAttribute* radiusAttr = new BxIntAttribute("radius", 5);
            newItem->addAttribute(radiusAttr);
            newItem->setPos(event->scenePos());


            insertActor(newItem);
            setMode(moveItem);
            break;
        }
        case editCamera:
        {
            if(mCameraPath)
            {
                mCameraPath->addPoint(event->scenePos());
            }
            else
            {
                mCameraPath = new BxNodePath(this);
            }
            break;
        }
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
        if(mMode == editCamera)
        {
            emit(cameraComplete());
            setMode(moveItem);
        }
        else
        {
            emit(itemDeleted()); // clearAttributeEditor before deleting item
            QList<QGraphicsItem*>items = this->selectedItems();
            foreach(auto i, items)
            {
                BxNodeActor* actor = dynamic_cast<BxNodeActor*>(i);
                if(actor)
                {
                    removeItem(actor);
                    delete actor;
                }
            }
        }
    }
}

void BxLevelScene::insertActor(BxNodeActor* in)
{
    addItem(in);
    emit(itemInserted());
}

