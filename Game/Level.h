#pragma once
#include "Game.h"
#include "NObject.h"
#include "Assets/ExternalDbAsset.h"

namespace Game
{

class GAME_EXPORT LevelType : public Nomad::Editor::ExternalDbAsset
  {
  S_ENTITY(LevelType, ExternalDbAsset)

public:
  const char *extension() const X_OVERRIDE;
  Nomad::Asset *defaultCreate(CreateInterface *c) X_OVERRIDE;
  };

class GAME_EXPORT Level : public Nomad::Asset
  {
  S_ENTITY(Level, Asset)

public:
  };

}
