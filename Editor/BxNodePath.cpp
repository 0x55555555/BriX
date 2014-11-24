#include "BxNodePath.h"
#include <QJsonObject>

BxNodePath::BxNodePath(QGraphicsScene* scene)
{
    mScene = scene;
}

void BxNodePath::writeToJson(QJsonObject& JsonPath)
{
    QJsonObject JsonPoints;
    /*
    int i = 0;
    foreach(auto point, mPoints)
    {
        QJsonObject JsonPos;
        point->writeToJson(JsonPos);
        JsonPoints[QString::number(i)] = JsonPos;
        i++;
    }
    */
    for(int i = 0; i < mPoints.length(); i++)
    {
        QJsonObject JsonPos;
        mPoints[i]->writeToJson(JsonPos);
        JsonPoints[QString::number(i)] = JsonPos;
    }
    JsonPath["path"] = JsonPoints;
}

void BxNodePath::readFromJson(const QJsonObject &)
{

}


void BxNodePath::addPoint(const QPointF &in)
{
    BxNodePathPoint* newPoint = new BxNodePathPoint(0, mScene);
    newPoint->setPos(in);

    if(!mPoints.empty())
    {
        BxNodeLine* newLine = new BxNodeLine(newPoint, mPoints.last()); // add line to both nodes connected
        newPoint->mConnections.push_back(newLine);
        mPoints.last()->mConnections.push_back(newLine);

        newLine->adjust();

        mScene->addItem(newLine);
    }

    mPoints.push_back(newPoint);
    mScene->addItem(newPoint);
}
