#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <utility>
#include <vector>
#include <QWidget>

#include "constants.h"
#include "../Controller/npc_controller.h"
#include "../GameObject/fireball.h"
#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Util/vector.h"

class Model {
 public:
  Model() = default;

  const Hero& GetHero() const;
  Hero& GetHero();

  const Map& GetMap() const;
  Map& GetMap();

  const NpcController& GetNpcController() const;
  NpcController& GetNpcController();

  void LoadPictures();

  std::vector<Fireball>& GetFireballs();
  const std::vector<Fireball>& GetFireballs() const;

  void AddFireball(const Fireball& fireball);

  std::vector<GameObject*> GetAllGameObjects();

 private:
  Hero hero_;
  Map map_;
  NpcController npc_controller_;
  std::vector<Fireball> fireballs_;
};

#endif  // MODEL_MODEL_H_
