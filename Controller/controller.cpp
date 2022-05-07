#include "controller.h"

#include <cassert>
#include <utility>
#include <vector>

void Controller::SetModel(std::unique_ptr<Model>&& model) {
  assert(model != nullptr);
  model_ = std::move(model);
}

void Controller::SetView(std::unique_ptr<View>&& view) {
  assert(view != nullptr);
  view_ = std::move(view);
}

void Controller::ConnectTimer() {
  timer_->setInterval(constants::kTickTime);
  connect(timer_, &QTimer::timeout, this, &Controller::TimerTick);
}

const Model& Controller::GetModel() const {
  return *model_;
}

void Controller::Start() {
  view_->CreateMenu();
  model_->GetMap().SetSize(view_->GetWindowWidth(), view_->GetWindowHeight());
  model_->LoadPictures();
  view_->show();
}

void Controller::StartGame() {
  view_->ShowGame();
  timer_->start();
}

void Controller::NewGame() {
  model_->GetHero().SetPosition(Point());
  // set default parameters to all objects

  StartGame();
}

void Controller::Pause() {
  view_->ShowMenu();
  timer_->stop();
}

void Controller::ChangeLanguage(Language language) {
  // todo
}

void Controller::ChangeSoundOn() {
  // todo
}

void Controller::TimerTick() {
  model_->GetHero().Move(GetHeroDirection(),
                         view_->GetWindowWidth(),
                         view_->GetWindowHeight());

  for (auto& fireball : model_->GetFireballs()) {
    fireball.Move();
  }

  // todo collisions with other objects

  std::vector<Fireball>& fireballs = model_->GetFireballs();
  int height = view_->GetWindowHeight();
  int width = view_->GetWindowWidth();
  for (int i = 0; i < fireballs.size(); ++i) {
    bool is_collided_with_left_wall =
        (fireballs[i].GetPosition().GetX() - constants::kFireballSize / 2
            <= -constants::kEpsilon);
    bool is_collided_with_right_wall =
        (fireballs[i].GetPosition().GetX() + constants::kFireballSize / 2
            - width >= constants::kEpsilon);
    bool is_collided_with_top_wall =
        (fireballs[i].GetPosition().GetY() - constants::kFireballSize / 2
            <= -constants::kEpsilon);
    bool is_collided_with_bottom_wall =
        (fireballs[i].GetPosition().GetY() + constants::kFireballSize / 2
            - height >= constants::kEpsilon);

    if (is_collided_with_left_wall || is_collided_with_right_wall ||
        is_collided_with_top_wall || is_collided_with_bottom_wall) {
      fireballs.erase(fireballs.begin() + i);
      --i;
    }
  }

  view_->repaint();
  ++counter_;
  counter_ %= constants::kSlowAnimation * constants::kNumberAnimation;

  if (is_striking_) {
    number_hero_++;
    if (number_hero_ == constants::kSlowAnimation *
        constants::kNumberAnimation) {
      number_hero_ = 0;
      is_striking_ = false;
    }
  }

  int counter2;
  for (auto& fireball : fireballs) {
    counter2 = fireball.GetCounter();
    if (fireball.IsBorn()) {
      if (fireball.GetCounter() == constants::kNumberBorn *
          constants::kSlowFireBall) {
        fireball.SetCounter(0);
        fireball.SetBorn(false);
      }
      fireball.SetCounter(counter2 + 1);
    } else {
      fireball.SetCounter((counter2 + 1) % (constants::kSlowFireBall
          * constants::kNumberFireBall));
    }
  }
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

int Controller::GetCounter() const {
  return counter_;
}

int Controller::GetHeroCurrentFrame() const {
  return number_hero_;
}

void Controller::HandleMousePressEvent(QMouseEvent* event) {
  Point spawn_pos = model_->GetHero().GetPosition();
  spawn_pos.SetX(spawn_pos.GetX() + constants::kHeroSize / 2);
  spawn_pos.SetY(spawn_pos.GetY() + constants::kHeroSize / 1.65);

  Vector2D direction(spawn_pos, Point(event->pos().x(), event->pos().y()));
  direction.Normalize();

  model_->AddFireball(Fireball(spawn_pos, direction));
  is_striking_ = true;
  number_hero_ = 0;
}
