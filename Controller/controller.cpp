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

const Hero& Controller::GetHero() const {
  return model_->GetHero();
}

const Map& Controller::GetMap() const {
  return model_->GetMap();
}

void Controller::Start() {
  model_->GetMap().SetSize(view_->GetWindowWidth(), view_->GetWindowHeight());
  model_->LoadPictures();
  view_->show();
  timer_->start();
}

void Controller::TimerTick() {
  model_->GetHero().Move(GetDirection(),
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
    if (fireballs[i].GetPosition().GetX() - constants::kFireballSize / 2
        <= -constants::kEpsilon ||
        fireballs[i].GetPosition().GetX() + constants::kFireballSize / 2
        - width >= constants::kEpsilon ||
        fireballs[i].GetPosition().GetY() - constants::kFireballSize / 2
        <= -constants::kEpsilon ||
        fireballs[i].GetPosition().GetY() + constants::kFireballSize / 2
        - height >= constants::kEpsilon) {
      fireballs.erase(fireballs.begin() + i);
      --i;
    }
  }

  view_->repaint();
  ++counter_;
  counter_ %= constants::kSlowAnimation * constants::kNumberAnimation;
}

void Controller::HandleKeyPressEvent(QKeyEvent* event) {
  keys_[event->key()] = true;
}

void Controller::HandleKeyReleaseEvent(QKeyEvent* event) {
  keys_[event->key()] = false;
}

Vector2D Controller::GetDirection() const {
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

const Model& Controller::GetModel() const {
  return *model_;
}

void Controller::HandleMousePressEvent(QMouseEvent* event,
                                       const Point& mouse_pos) {
  is_clicked_ = true;
  Point spawn_pos = model_->GetHero().GetPosition();
  spawn_pos.SetX(spawn_pos.GetX() + constants::kHeroSize / 2);
  spawn_pos.SetY(spawn_pos.GetY() + constants::kHeroSize / 1.5);

  Vector2D direction(spawn_pos, mouse_pos);
  direction.Normalize();

  Fireball fireball(spawn_pos, direction);
  model_->AddFireball(fireball);
}

void Controller::HandleMouseReleaseEvent(QMouseEvent* event) {
  is_clicked_ = false;
}
