#include "controller.h"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <QSettings>

void Controller::SetModel(std::unique_ptr<Model>&& model) {
  assert(model != nullptr);
  model_ = std::move(model);
}

void Controller::SetView(std::unique_ptr<View>&& view) {
  assert(view != nullptr);
  view_ = std::move(view);
}

void Controller::ReadSettings() {
  QSettings settings("Merciless procrastinators", "Demons");
  is_sound_on_ = settings.value("IsSoundOn", true).toBool();
}

void Controller::WriteSettings() {
  QSettings settings("Merciless procrastinators", "Demons");
  settings.setValue("IsSoundOn", is_sound_on_);
}

void Controller::ConnectTimer() {
  timer_->setInterval(constants::kTickTime);
  connect(timer_, &QTimer::timeout, this, &Controller::TimerTick);
  music_timer_->setInterval(constants::kMusicTickTime);
  connect(music_timer_, &QTimer::timeout, this, &Controller::MusicTick);
}

const Model& Controller::GetModel() const {
  return *model_;
}

void Controller::Start() {
  ReadSettings();
  view_->CreateMenus();
  model_->GetMap().SetSize(view_->GetWindowWidth(), view_->GetWindowHeight());
  model_->GetMap().LoadBoilers();
  model_->LoadPictures();
  view_->LoadPictures();
  model_->LoadSounds();
  model_->SetMuted(!is_sound_on_);
  view_->show();
  music_timer_->start();
  model_->GetSound(Sound::kMenuMusic).play();
}

void Controller::StartGame() {
  view_->ShowGame();
  timer_->start();
  model_->GetSound(Sound::kMenuMusic).stop();
  model_->GetSound(Sound::kBackgroundMusic).play();
  music_counter_ = 0;
}

void Controller::NewGame() {
  model_->GetHero().SetHealthPoints(constants::kHeroHealthPoints);
  model_->SetProgress(0);
  model_->GetHero().SetPosition(Point(constants::kHeroSize / 2.,
                                      constants::kHeroSize / 2.));
  model_->GetFireballs().clear();
  model_->GetHero().SetNumberTick(0);
  model_->GetNpcController().ClearNpcList();
  counter_ = 0;

  StartGame();
}

void Controller::Pause() {
  view_->ShowMenu();
  timer_->stop();

  StopGameSounds();
  model_->GetSound(Sound::kMenuMusic).play();
  music_counter_ = 0;
}

void Controller::CheckEndOfGame() {
  if (model_->GetHero().GetHealthPoints() < constants::kEpsilon) {
    timer_->stop();
    StopGameSounds();
    model_->GetSound(Sound::kDefeatMusic).play();
    music_counter_ = 0;
    view_->ShowDefeatEnd();
    return;
  }
  if (model_->GetProgress() == constants::kGoalKills) {
    timer_->stop();
    StopGameSounds();
    model_->GetSound(Sound::kVictoryMusic).play();
    music_counter_ = 0;
    view_->ShowVictoryEnd();
  }
}

void Controller::ShowMenuAfterEndOfGame() {
  model_->GetSound(Sound::kVictoryMusic).stop();
  model_->GetSound(Sound::kDefeatMusic).stop();
  model_->GetSound(Sound::kMenuMusic).play();
  music_counter_ = 0;
  view_->ShowMenuAfterEndOfGame();
}

void Controller::ChangeLanguage(Language language) {
  // todo
}

void Controller::ChangeSoundOn() {
  is_sound_on_ = !is_sound_on_;
  model_->SetMuted(!is_sound_on_);
  model_->GetSound(Sound::kMenuMusic).stop();
  model_->GetSound(Sound::kMenuMusic).play();
  music_counter_ = 0;
}

void Controller::HandleKeyPressEvent(QKeyEvent* event) {
  if (!timer_->isActive()) return;
  if (event->key() == Qt::Key_Space) {
    Pause();
  }
  keys_[event->key()] = true;
}

void Controller::HandleKeyReleaseEvent(QKeyEvent* event) {
  keys_[event->key()] = false;
}

int Controller::GetCounter() const {
  return counter_;
}

bool Controller::IsSoundOn() const {
  return is_sound_on_;
}

void Controller::TimerTick() {
  model_->GetNpcController().IncrementTickCounter();
  if (model_->GetNpcController().NeedToCreateNpc()) {
    model_->GetNpcController().CreateNpc(model_->GetHero().GetPosition(),
                                         model_->GetMap());
    model_->GetNpcController().CreateNpc(model_->GetHero().GetPosition(),
                                         model_->GetMap());
    model_->GetSound(Sound::kNpcAppearance).play();
  }

  Point old_hero_position = model_->GetHero().GetPosition();
  std::vector<Point> old_npc_coords =
      model_->GetNpcController().GetNpcCoordinates();

  HandleNpcsAttack();

  MoveObjects();

  HandleHeroAfkStanding(old_hero_position);

  collisions_controller_.CheckCollisions(model_,
                                         old_hero_position,
                                         old_npc_coords,
                                         view_->GetWindowWidth(),
                                         view_->GetWindowHeight());


  collisions_controller_.PrepareForDrawing(model_);

  if (collisions_controller_.SomeoneWasKilled()) {
    model_->GetSound(Sound::kHeroShot).stop();
    model_->GetSound(Sound::kHeroShot).play();
  }

  ++counter_;
  counter_ %= constants::kHeroSpeedCoefficient * constants::kNumberOfAnimation;

  UpdateHeroFieldsForDrawing();
  UpdateFireballsFieldsForDrawing();

  view_->repaint();

  CheckEndOfGame();
}

Vector2D Controller::GetHeroDirection() const {
  Vector2D direction;
  if ((keys_.contains(Qt::Key_Left) && keys_.at(Qt::Key_Left))
      || (keys_.contains(Qt::Key_A) && keys_.at(Qt::Key_A))) {
    direction += {-1, 0};
  }
  if ((keys_.contains(Qt::Key_Up) && keys_.at(Qt::Key_Up))
      || (keys_.contains(Qt::Key_W) && keys_.at(Qt::Key_W))) {
    direction += {0, -1};
  }
  if ((keys_.contains(Qt::Key_Right) && keys_.at(Qt::Key_Right))
      || (keys_.contains(Qt::Key_D) && keys_.at(Qt::Key_D))) {
    direction += {1, 0};
  }
  if ((keys_.contains(Qt::Key_Down) && keys_.at(Qt::Key_Down))
      || (keys_.contains(Qt::Key_S) && keys_.at(Qt::Key_S))) {
    direction += {0, 1};
  }
  direction.Normalize();
  return direction;
}

void Controller::HandleMousePressEvent(QMouseEvent* event) {
  Point spawn_pos = model_->GetHero().GetPosition()
      + Point(0, constants::kHeroSize * constants::kTorsoPercentage);

  model_->AddFireball(Fireball(spawn_pos,
                               Point(event->pos().x(), event->pos().y())));
  model_->GetHero().SetStrikingStatus(true);
  model_->GetHero().SetNumberTick(0);
}

void Controller::MoveObjects() {
  model_->GetHero().Move(GetHeroDirection(),
                         view_->GetWindowWidth(),
                         view_->GetWindowHeight());

  model_->GetNpcController().Update(model_->GetHero().GetPosition(),
                                    model_->GetMap());

  Point spawn_pos = model_->GetHero().GetPosition()
      + Point(0, constants::kHeroSize * constants::kTorsoPercentage);
  for (auto& fireball : model_->GetFireballs()) {
    fireball.Move(spawn_pos);
  }
}

void Controller::UpdateHeroFieldsForDrawing() {
  if (model_->GetHero().IsStriking()) {
    model_->GetHero().SetNumberTick(
        model_->GetHero().GetNumberTick() + 1);
    if (model_->GetHero().GetNumberTick()
        == constants::kHeroSpeedCoefficient * constants::kNumberOfAnimation) {
      model_->GetHero().SetNumberTick(0);
      model_->GetHero().SetStrikingStatus(false);
    }
  }
}

void Controller::UpdateFireballsFieldsForDrawing() {
  std::vector<Fireball>& fireballs = model_->GetFireballs();
  for (auto& fireball : fireballs) {
    int current_counter = fireball.GetCounter();
    if (fireball.IsBorn()) {
      if (fireball.GetCounter() + 1 == constants::kNumberOfBornFireballs *
          constants::kFireballSpeedCoefficient) {
        fireball.SetCounter(0);
        fireball.SetBorn(false);
        fireball.CreateDirection();
      } else {
        fireball.SetCounter(current_counter + 1);
      }
    } else {
      fireball.SetCounter(
          (current_counter + 1) % (constants::kFireballSpeedCoefficient
              * constants::kNumberOfFireBall));
    }
  }
}

int Controller::GetMaxRenderingLevel() const {
  int result = 0;

  auto all_objects = model_->GetAllGameObjects();
  for (const auto& object : all_objects) {
    result = std::max(result, object->GetRenderingLevel());
  }
  return result;
}

void Controller::HandleHeroAfkStanding(const Point& old_hero_pos) {
  if (model_->GetHero().GetPosition() == old_hero_pos) {
    model_->GetHero().IncrementStandingTicks();
  } else {
    model_->GetHero().SetStandingTicks(0);
  }

  if (model_->GetHero().GetStandingTicks() >=
      constants::kStandingTicksToGetLavaDamage) {
    model_->GetHero().SetHealthPoints(model_->GetHero().GetHealthPoints()
    - constants::kLavaDamage);
  }
}

void Controller::HandleNpcsAttack() {
  for (auto& npc : model_->GetNpcController().GetNpcList()) {
    npc.CheckFighting();
  }

  for (const auto& npc : model_->GetNpcController().GetNpcList()) {
    if (npc.IsFighting() && npc.GetCounter() ==
        constants::kNpcSpeedCoefficient * constants::kNumberOfRaisingHandNpc) {
      npc.AttackHero(&model_->GetHero());
      model_->GetSound(Sound::kNpcHit).stop();
      model_->GetSound(Sound::kNpcHit).play();
    }
  }
}

void Controller::MusicTick() {
  ++music_counter_;
  auto current_music = model_->GetCurrentMusic();
  switch (current_music) {
    case Sound::kMenuMusic: {
      if (constants::kMenuMusicDuration - music_counter_
            <= constants::kMusicComparisonConstant) {
        model_->GetSound(current_music).stop();
        model_->GetSound(current_music).play();
        music_counter_ = 0;
      }
      break;
    }
    case Sound::kBackgroundMusic: {
      if (constants::kBackgroundMusicDuration - music_counter_
            <= constants::kMusicComparisonConstant) {
        model_->GetSound(current_music).stop();
        model_->GetSound(current_music).play();
        music_counter_ = 0;
      }
      break;
    }
    case Sound::kVictoryMusic: {
      if (constants::kVictoryMusicDuration - music_counter_
            <= constants::kMusicComparisonConstant + 7) {
        model_->GetSound(current_music).stop();
        model_->GetSound(current_music).play();
        music_counter_ = 0;
      }
      break;
    }
    case Sound::kDefeatMusic: {
      if (constants::kDefeatMusicDuration - music_counter_
            <= constants::kMusicComparisonConstant) {
        model_->GetSound(current_music).stop();
        model_->GetSound(current_music).play();
        music_counter_ = 0;
      }
      break;
    }
    default:
      return;
  }
}

void Controller::StopGameSounds() {
  model_->GetSound(Sound::kBackgroundMusic).stop();
  model_->GetSound(Sound::kHeroShot).stop();
  model_->GetSound(Sound::kNpcHit).stop();
  model_->GetSound(Sound::kNpcAppearance).stop();
}
