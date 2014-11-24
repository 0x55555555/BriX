#include "BxNodeLine.h"
#include <QPainter>

BxNodeLine::BxNodeLine(BxNodePathPoint* src, BxNodePathPoint* dest)
{
    mSrc = src;
    mDest = dest;
}

void BxNodeLine::adjust()
{
    if (!mSrc || !mDest)
        return;

    prepareGeometryChange();
    update(boundingRect());
}

QRectF BxNodeLine::boundingRect() const
{
    float x, y, w, h;

    if(mSrc->x() < mDest->x())
    {
        x = mSrc->x();
        w = mDest->x() - mSrc->x();
    }
    else
    {
        x = mDest->x();
        w = mSrc->x() - mDest->x();
    }
    if(mSrc->y() < mDest->y())
    {
        y = mSrc->y();
        h = mDest->y() - mSrc->y();
    }
    else
    {
        y = mDest->y();
        h = mSrc->y() - mDest->y();
    }
    return QRectF(x, y, w, h);
}

void BxNodeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!mSrc || !mDest)
    {
        return;
    }

    QPen p = painter->pen();
    QLineF line(mapFromItem(mSrc, 0, 0), mapFromItem(mDest, 0, 0));
    painter->setBrush(Qt::black);
    painter->drawLine(line);
}
