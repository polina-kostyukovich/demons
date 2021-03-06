#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <QMediaPlayer>
#include <QWidget>

#include "constants.h"
#include "../Controller/npc_controller.h"
#include "../GameObject/fireball.h"
#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Util/structs.h"
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
  void LoadSounds();

  const QMediaPlayer& GetSound(Sound sound) const;
  QMediaPlayer& GetSound(Sound sound);

  void SetMuted(bool is_muted);
  Sound GetCurrentMusic() const;

  std::vector<Fireball>& GetFireballs();
  const std::vector<Fireball>& GetFireballs() const;

  void AddFireball(const Fireball& fireball);

  std::vector<GameObject*> GetAllGameObjects();

  int GetProgress() const;
  void SetProgress(int);

 private:
  Hero hero_;
  Map map_;
  NpcController npc_controller_;
  std::vector<Fireball> fireballs_;
  int progress_{0};
  std::map<Sound, QMediaPlayer> sounds_;
};

#endif  // MODEL_MODEL_H_
