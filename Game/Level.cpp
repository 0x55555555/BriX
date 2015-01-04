#include "Level.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "NObject.h"
#include "NObjectInstance.h"
#include "NAssetManager.h"
#include "Assets/ObjectType.h"
#include "AssetSelector.h"
#include "Renderable.h"
#include "RCCamera.h"
#include "shift/Properties/sdata.inl"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QVBoxLayout"
#include "XTransform.h"
#include "PreviewViewport.h"

namespace Game
{

S_IMPLEMENT_PROPERTY(LevelType, Game)

void LevelType::createTypeInformation(
    Shift::PropertyInformationTyped<LevelType> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto scale = childBlock.add(&LevelType::scale, "scale");
  scale->setDefaultValue(0.01f);

  auto player = childBlock.add(&LevelType::playerShip, "playerShip");
  player->setResolveFunction(Nomad::AssetManager::resolveAssetPointer);
  }

const char *LevelType::extension() const
  {
  return "lev";
  }

Nomad::Asset *LevelType::processSource(const QByteArray &source, CreateInterface *)
  {
  auto lev = assetParent()->add<Level>();

  // Todo - dont pick the first renderable.
  Nomad::Object *ship = playerShip.pointed<Nomad::Object>();
  if (ship == nullptr)
    {
    addError(X_CURRENT_CODE_LOCATION_DETAILED, "Bad player ship specified");
    return nullptr;
    }

  QJsonDocument doc(QJsonDocument::fromJson(source));

  Eks::BoundingBox bounds;

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

    auto inst = lev->addInstance(ship);

    auto txData = inst->firstChild<Nomad::RenderableInstance>();
    xAssert(txData);

    Eks::Transform tx = Eks::Transform::Identity();
    tx.scale(rad * scale());
    tx.translation() = Eks::Vector3D(x * scale(), 0.0f, y * scale());

    Eks::BoundingBox box;
    box.unite(tx.translation());
    box.expand(1);

    bounds.unite(box);

    txData->transform = tx;
    lev->scene.renderGroup.addPointer(txData);
    }

  auto cam = lev->scene.children.add<RCPerspectiveCamera>();
  cam->viewportWidth = 1;
  cam->viewportWidth = 1;
  lev->scene.setCamera(cam);

  cam->transform = Eks::TransformUtilities::lookAt(Eks::Vector3D(0, 1, -0.5), Eks::Vector3D::Zero(), Eks::Vector3D(0, 0, 1));
  cam->moveToFit(bounds);

  return lev;
  }

QByteArray LevelType::defaultSource() const
  {
  return "{\n"
"  \"actors\": ["
"  ]\n"
"}";
  }

QWidget *LevelType::createEditor(Nomad::Editor::ProjectInterface *ifc, CreateInterface *c)
  {
  QWidget *w = new QWidget();
  QVBoxLayout *l = new QVBoxLayout();
  l->setContentsMargins(0, 0, 0, 0);
  w->setLayout(l);

  auto box = new Nomad::Editor::AssetSelector(ifc, c, &playerShip, Nomad::Editor::ObjectType::staticTypeInformation(), w);
  QObject::connect(box, &Nomad::Editor::AssetSelector::assetChanged, [this, c]()
    {
    reinitialise(source(), c);
    });
  l->addWidget(box);

  auto editor = ExternalSourceAsset::createEditor(ifc, c);
  editor->setParent(w);
  l->addWidget(editor);

  return w;
  }

QWidget *LevelType::createPreview(Nomad::Editor::UIInterface *ifc, CreateInterface *c)
  {
  struct LevelViewport : public Nomad::Editor::PreviewViewport
    {
    LevelViewport(Nomad::Editor::UIInterface *ifc, CreateInterface *c, LevelType *m)
        : PreviewViewport(ifc),
          createInterface(c),
          level(m)
      {
      }

    void resize3D(Eks::Renderer *, xuint32 w, xuint32 h)
      {
      auto ass = level->asset(createInterface);
      if (!ass)
        {
        return;
        }

      auto l = ass->castTo<Level>();

      l->scene.activeCamera()->viewportWidth = w;
      l->scene.activeCamera()->viewportHeight = h;
      }

    void renderGeometry(Eks::Renderer *r) X_OVERRIDE
      {
      auto ass = level->asset(createInterface);
      if (!ass)
        {
        return;
        }

      auto l = ass->castTo<Level>();
      l->scene.renderer = r;
      RCRenderable::RenderState state = { nullptr, Eks::Transform::Identity() };

      l->scene.render(r, state);
      }

    CreateInterface *createInterface;
    LevelType *level;
    };

  return new LevelViewport(ifc, c, this);
  }

S_IMPLEMENT_PROPERTY(Level, Game)

void Level::createTypeInformation(
    Shift::PropertyInformationTyped<Level> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  childBlock.add(&Level::scene, "scene");
  }
}
