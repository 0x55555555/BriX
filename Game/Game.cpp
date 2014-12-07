#include "Game.h"
#include "shift/TypeInformation/smodule.h"
#include "shift/Properties/sattribute.inl"

S_IMPLEMENT_MODULE(Game)

/*
QFile loadFile("/Volumes/User/BriX/Game/deets.json");

if (!loadFile.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file.");
    return;
}

float scale = 0.01f;

QByteArray saveData = loadFile.readAll();
QJsonDocument doc(QJsonDocument::fromJson(saveData));

QJsonArray arr = doc.object()["actors"].toArray();
for (int i = 0; i < arr.size(); ++i)
  {
  QJsonObject obj(arr[i].toObject());

  auto first = obj.begin();
  QJsonObject data = first.value().toObject();

  auto pos = data["pos"].toObject();
  auto x = pos["x"].toDouble();
  auto y = pos["y"].toDouble();

  auto attr = data["attr"].toObject();
  auto rad = attr["radius"].toDouble();

  drawSphere(x * scale, y * scale, rad * scale);
  }
*/
