#include "model.h"

#include <limits>

const Hero& Model::GetHero() const {
  return hero_;
}

Hero& Model::GetHero() {
  return hero_;
}

const Map& Model::GetMap() const {
  return map_;
}

Map& Model::GetMap() {
  return map_;
}

const NpcController& Model::GetNpcController() const {
  return npc_controller_;
}

NpcController& Model::GetNpcController() {
  return npc_controller_;
}

void Model::LoadPictures() {
  hero_.LoadPictures();
  map_.LoadPictures();
  Fireball::LoadPictures();
  Npc::LoadPictures();
}

void Model::LoadSounds() {
  sounds_[Sound::kBackgroundMusic].setSource(QUrl("qrc:/Resources/Music/background.wav"));
  sounds_[Sound::kHeroShot].setSource(QUrl("qrc:/Resources/Music/shot.wav"));
  sounds_[Sound::kMenuMusic].setSource(QUrl("qrc:/Resources/Music/menu.wav"));
  sounds_[Sound::kNpcAppearance].setSource(QUrl("qrc:/Resources/Music/appearance.wav"));
  sounds_[Sound::kNpcHit].setSource(QUrl("qrc:/Resources/Music/hit.wav"));

  sounds_[Sound::kMenuMusic].setLoopCount(std::numeric_limits<int>::max());

  sounds_[Sound::kBackgroundMusic].setVolume(0.2);
  sounds_[Sound::kHeroShot].setVolume(0.4);
  sounds_[Sound::kMenuMusic].setVolume(0.1);
  sounds_[Sound::kNpcAppearance].setVolume(1);
  sounds_[Sound::kNpcHit].setVolume(0.8);
}

const QSoundEffect& Model::GetSound(Sound sound) const {
  return sounds_.at(sound);
}

QSoundEffect& Model::GetSound(Sound sound) {
  return sounds_.at(sound);
}

void Model::SetMuted(bool is_muted) {
  sounds_[Sound::kBackgroundMusic].setMuted(is_muted);
  sounds_[Sound::kHeroShot].setMuted(is_muted);
  sounds_[Sound::kMenuMusic].setMuted(is_muted);
  sounds_[Sound::kNpcAppearance].setMuted(is_muted);
  sounds_[Sound::kNpcHit].setMuted(is_muted);
}

std::vector<Fireball>& Model::GetFireballs() {
  return fireballs_;
}
const std::vector<Fireball>& Model::GetFireballs() const {
  return fireballs_;
}
void Model::AddFireball(const Fireball& fireball) {
  fireballs_.emplace_back(fireball);
}
