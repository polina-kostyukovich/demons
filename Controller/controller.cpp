#include "controller.h"

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
}

const Model& Controller::GetModel() const {
  return *model_;
}

void Controller::Start() {
  ReadSettings();
  view_->CreateMenu();
  model_->GetMap().SetSize(view_->GetWindowWidth(), view_->GetWindowHeight());
  model_->GetMap().LoadBoilers();
  model_->LoadPictures();
  model_->LoadSounds();
  model_->SetMuted(!is_sound_on_);
  view_->show();
  model_->GetSound(Sound::kMenuMusic).play();
}

void Controller::StartGame() {
  view_->ShowGame();
  timer_->start();
  model_->GetSound(Sound::kMenuMusic).stop();
  model_->GetSound(Sound::kBackgroundMusic).play();
}

void Controller::NewGame() {
  model_->GetHero().SetPosition(Point(constants::kHeroSize / 2.,
                                      constants::kHeroSize / 2.));
  model_->GetFireballs().clear();
  model_->GetHero().SetNumberTick(0);
  counter_ = 0;
  // set default parameters to all objects

  StartGame();
}

void Controller::Pause() {
  view_->ShowMenu();
  timer_->stop();
  model_->GetSound(Sound::kBackgroundMusic).stop();
  model_->GetSound(Sound::kMenuMusic).play();
}

void Controller::ChangeLanguage(Language language) {
  // todo
}

void Controller::ChangeSoundOn() {
  is_sound_on_ = !is_sound_on_;
  model_->SetMuted(!is_sound_on_);
}

void Controller::HandleKeyPressEvent(QKeyEvent* event) {
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
  if (!model_->GetSound(Sound::kBackgroundMusic).isPlaying()) {
    model_->GetSound(Sound::kBackgroundMusic).play();
  }

  model_->GetHero().Move(GetHeroDirection(),
                         view_->GetWindowWidth(),
                         view_->GetWindowHeight());
  model_->GetNpcController().Update(model_->GetHero().GetPosition());

  // todo collisions with other objects

  ++counter_;
  counter_ %= constants::kHeroSpeedCoefficient * constants::kNumberOfAnimation;

  Point spawn_pos = model_->GetHero().GetPosition()
      + Point(0, constants::kHeroSize * constants::kTorsoPercentage);
  for (auto& fireball : model_->GetFireballs()) {
    fireball.Move(spawn_pos);
  }

  CheckFireballsCollisionsWithWalls();

  UpdateHeroFields();
  UpdateFireballsFields();

  view_->repaint();
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
  model_->GetHero().SetStriking(true);
  model_->GetHero().SetNumberTick(0);
}

void Controller::CheckFireballsCollisionsWithWalls() {
  std::vector<Fireball>& fireballs = model_->GetFireballs();
  int height = view_->GetWindowHeight();
  int width = view_->GetWindowWidth();
  for (int i = 0; i < fireballs.size(); ++i) {
    bool is_collided_with_left_wall =
        (fireballs[i].GetPosition().GetX() - constants::kFireballSize / 2.
            <= -constants::kEpsilon);
    bool is_collided_with_right_wall =
        (fireballs[i].GetPosition().GetX() + constants::kFireballSize / 2.
            - width >= constants::kEpsilon);
    bool is_collided_with_top_wall =
        (fireballs[i].GetPosition().GetY() - constants::kFireballSize / 2.
            <= -constants::kEpsilon);
    bool is_collided_with_bottom_wall =
        (fireballs[i].GetPosition().GetY() + constants::kFireballSize / 2.
            - height >= constants::kEpsilon);

    if (is_collided_with_left_wall || is_collided_with_right_wall ||
        is_collided_with_top_wall || is_collided_with_bottom_wall) {
      fireballs.erase(fireballs.begin() + i);
      --i;
    }
  }
}

void Controller::UpdateHeroFields() {
  if (model_->GetHero().IsStriking()) {
    model_->GetHero().SetNumberTick(
        model_->GetHero().GetNumberTick() + 1);
    if (model_->GetHero().GetNumberTick()
        == constants::kHeroSpeedCoefficient * constants::kNumberOfAnimation) {
      model_->GetHero().SetNumberTick(0);
      model_->GetHero().SetStriking(false);
    }
  }
}
void Controller::UpdateFireballsFields() {
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
