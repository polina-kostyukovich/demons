#include "model.h"

#include <string>
#include <QAudioOutput>

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
  std::vector<std::string> names = {
        "qrc:/Resources/Music/menu.mp3",
        "qrc:/Resources/Music/background.mp3",
        "qrc:/Resources/Music/appearance.mp3",
        "qrc:/Resources/Music/hit.mp3",
        "qrc:/Resources/Music/shot.mp3",
        "qrc:/Resources/Music/victory.mp3",
        "qrc:/Resources/Music/defeat.mp3",
  };

  for (int i = 0; i < constants::kNumberOfSounds; ++i) {
    auto audioOutput = new QAudioOutput;
    sounds_[static_cast<Sound>(i)].setAudioOutput(audioOutput);
    sounds_[static_cast<Sound>(i)].setSource(QUrl(names[i].c_str()));
  }
}

const QMediaPlayer& Model::GetSound(Sound sound) const {
  return sounds_.at(sound);
}

QMediaPlayer& Model::GetSound(Sound sound) {
  return sounds_.at(sound);
}

void Model::SetMuted(bool is_muted) {
  for (int i = 0; i < constants::kNumberOfSounds; ++i) {
    sounds_[static_cast<Sound>(i)].audioOutput()->setMuted(is_muted);
  }
}

Sound Model::GetCurrentMusic() const {
  if (sounds_.at(Sound::kMenuMusic).playbackState()
        == QMediaPlayer::PlayingState) {
    return Sound::kMenuMusic;
  }
  if (sounds_.at(Sound::kVictoryMusic).playbackState()
        == QMediaPlayer::PlayingState) {
    return Sound::kVictoryMusic;
  }
  if (sounds_.at(Sound::kDefeatMusic).playbackState()
        == QMediaPlayer::PlayingState) {
    return Sound::kDefeatMusic;
  }
  return Sound::kBackgroundMusic;
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

std::vector<GameObject*> Model::GetAllGameObjects() {
  std::vector<GameObject*> result;
  for (const auto& object : GetMap().GetObjects()) {
    result.emplace_back(object.get());
  }
  for (auto& object : GetFireballs()) {
    result.emplace_back(&object);
  }

  for (auto& object : GetNpcController().GetNpcList()) {
    result.emplace_back(&object);
  }

  result.emplace_back(&hero_);
  return result;
}

int Model::GetProgress() const {
  return progress_;
}
void Model::SetProgress(int progress) {
  progress_ = progress;
}


