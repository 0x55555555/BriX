#ifndef BXLEVELSCENE_H
#define BXLEVELSCENE_H

#include <QGraphicsScene>
#include "BxNodeActor.h"
#include "BxNodePath.h"

class BxLevelScene : public QGraphicsScene
{
    Q_OBJECT
public:

    enum Mode { insertItem, moveItem, moveView, editCamera };
    BxLevelScene();
    void insertActor(BxNodeActor*);
    int getMode(){ return mMode; }
    BxNodePath* getCameraPath(){ return mCameraPath; }
    
signals:

    void itemDeleted();
    void itemInserted();
    void cameraComplete();

protected:
    void keyPressEvent(QKeyEvent*);

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);


public slots:
    void setMode(int in){ mMode = in; }

private:
    BxNodePath* mCameraPath;
    int mMode;

    
};

#endif // BXLEVELSCENE_H
