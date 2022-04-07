#include "controller.h"

#include <utility>

Controller::Controller(std::unique_ptr<Model>&& model) :
    model_(std::move(model)),
    timer_(new QTimer(this)) {
  timer_->setInterval(constants::kTickTime);
  connect(timer_.get(), &QTimer::timeout, this, &Controller::TimerTick);
}

void Controller::TimerTick() {
  model_->MoveHero(GetDirection());
}

void Controller::keyPressEvent(QKeyEvent* event) {
  keys_[event->key()] = true;
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  keys_[event->key()] = false;
}

Vector2D Controller::GetDirection() const {
  Vector2D direction;
  if (keys_.contains(Qt::Key_Left) && keys_.at(Qt::Key_Left)
      || keys_.contains(Qt::Key_A) && keys_.at(Qt::Key_A)) {
    direction += {-1, 0};
  }
  if (keys_.contains(Qt::Key_Up) && keys_.at(Qt::Key_Up)
      || keys_.contains(Qt::Key_W) && keys_.at(Qt::Key_W)) {
    direction += {0, -1};
  }
  if (keys_.contains(Qt::Key_Right) && keys_.at(Qt::Key_Right)
      || keys_.contains(Qt::Key_D) && keys_.at(Qt::Key_D)) {
    direction += {1, 0};
  }
  if (keys_.contains(Qt::Key_Down) && keys_.at(Qt::Key_Down)
      || keys_.contains(Qt::Key_S) && keys_.at(Qt::Key_S)) {
    direction += {0, 1};
  }
  direction.Normalize();
  return direction;
}
