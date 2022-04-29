#include "controller.h"

#include <cassert>
#include <utility>

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

const Hero& Controller::GetHero() const {
  return model_->GetHero();
}

const Map& Controller::GetMap() const {
  return model_->GetMap();
}

void Controller::TimerTick() {
  model_->GetHero().Move(GetHeroDirection(),
                         view_->GetWindowWidth(),
                         view_->GetWindowHeight());
  view_->repaint();
  ++counter_;
  counter_ %= constants::kSlowAnimation * constants::kNumberAnimation;
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
