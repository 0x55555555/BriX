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
    update();
}

QRectF BxNodeLine::boundingRect() const
{
    QPointF src = mSrc->pos();
    QPointF dest = mDest->pos();
    QRectF rect(src, QSizeF(dest.x() - src.x(), dest.y() - src.y()));
    return rect;
}

void BxNodeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF r = boundingRect();
    QPen p = painter->pen();
    //painter->drawRect(QRectF(r.x(), r.y(), r.width()-p.width(), r.height()-p.width()));

    if(!mSrc || !mDest)
    {
        return;
    }

    QLineF line(mapFromItem(mSrc, 0, 0), mapFromItem(mDest, 0, 0));
    //QLineF line(mSrc->pos(), mDest->pos());
    painter->setBrush(Qt::black);
    painter->drawLine(line);
}
