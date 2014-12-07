#include "Level.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

namespace Game
{

S_IMPLEMENT_PROPERTY(LevelType, Game)

void LevelType::createTypeInformation(
    Shift::PropertyInformationTyped<LevelType> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);
  }

const char *LevelType::extension() const
  {
  return "lev";
  }

Nomad::Asset *LevelType::defaultCreate(CreateInterface *)
  {
  return assetParent()->add<Level>();
  }

S_IMPLEMENT_PROPERTY(Level, Game)

void Level::createTypeInformation(
    Shift::PropertyInformationTyped<Level> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);
  }
}
