#pragma once
#include "Game.h"
#include "NObject.h"
#include "Assets/ExternalSourceAsset.h"
#include "RCScene.h"

namespace Game
{

class GAME_EXPORT LevelType : public Nomad::Editor::ExternalSourceAsset
  {
  S_ENTITY(LevelType, ExternalSourceAsset)

public:
  const char *extension() const X_OVERRIDE;

  Nomad::Asset *processSource(const QByteArray &source, CreateInterface *c) X_OVERRIDE;
  QByteArray defaultSource() const X_OVERRIDE;

  QWidget *createEditor(Nomad::Editor::ProjectInterface *ifc, CreateInterface *c) X_OVERRIDE;
  QWidget *createPreview(Nomad::Editor::UIInterface *ifc, CreateInterface *c) X_OVERRIDE;

  Shift::ExternalUuidPointer playerShip;

  Shift::Data<float> scale;
  };

class GAME_EXPORT Level : public Nomad::Object
  {
  S_ENTITY(Level, Object)

public:

  RCScene scene;
  };

}
