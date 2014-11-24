#ifndef BXNODELINE_H
#define BXNODELINE_H

#include "BxNodePathPoint.h"

class BxNodePathPoint;

class BxNodeLine : public QGraphicsItem
{
public:
    BxNodeLine(BxNodePathPoint*, BxNodePathPoint*);

    void adjust();

protected:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    virtual QRectF boundingRect() const;

private:
    BxNodePathPoint* mSrc;
    BxNodePathPoint* mDest;

};

#endif // BXNODELINE_H
