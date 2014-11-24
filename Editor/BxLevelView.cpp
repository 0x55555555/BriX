#include "BxLevelView.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

BxLevelView::BxLevelView(BxLevelScene* in) :
    QGraphicsView(in)
{
    mTranslating = false;
    mScaling = false;
    mLastMouseXPos = 0;
    mScalePoint = QPointF(0, 0);
    mTransform = QTransform();
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void BxLevelView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Alt)
    {
        mScaling = true;
    }
    if(event->key() == Qt::Key_U)
    {
        /*
        QPointF scenePoint = mapToScene(mScalePoint);
        QPointF centrePoint = mapToScene(viewport()->rect().center());
        QPointF diff =  centrePoint - scenePoint;
        qDebug() << scenePoint;
        qDebug() << centrePoint;
        qDebug() << diff;

//        mTransform.reset();
//        mTransform.translate(diff.x(), diff.y());
//        mTransform.scale(1.1,1.1);
//        mTransform.translate(-diff.x(), -diff.y());
*/
//        setTransform(mTransform, 1);

        translate(-mScalePoint.x(),-mScalePoint.y());
        scale(1.1,1.1);
        translate(mScalePoint.x(),mScalePoint.y());
    }
    if(event->key() == Qt::Key_D)
    {
        scale(0.9,0.9);
    }
    if(event->key() == Qt::Key_C)
    {
        centerOn(0,0);
    }

    QGraphicsView::keyPressEvent(event);
}

void BxLevelView::keyReleaseEvent(QKeyEvent* event)
{
    mScaling = false;
    mTranslating = false;
    QGraphicsView::keyReleaseEvent(event);
}


void BxLevelView::mousePressEvent(QMouseEvent* event)
{
    if(mScaling)
    {
        mLastMouseXPos = event->globalX();
        mScalePoint = mapToScene(event->pos());
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void BxLevelView::mouseMoveEvent(QMouseEvent* event)
{
    if(mScaling)
    {
        float dMouseXPos = 1 + ((event->globalX() - mLastMouseXPos)/100.0f);
        translate(mScalePoint.x(),mScalePoint.y());
        scale(dMouseXPos,dMouseXPos);
        translate(-mScalePoint.x(),-mScalePoint.y());
        mLastMouseXPos = event->globalPos().x();
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void BxLevelView::mouseReleaseEvent(QMouseEvent* event)
{
    mLastMouseXPos = 0;
    QGraphicsView::mouseReleaseEvent(event);
}
