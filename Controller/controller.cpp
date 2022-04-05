#include "controller.h"

#include <utility>

Controller::Controller(std::unique_ptr<Model>&& model) :
    model_(std::move(model)),
    timer_(new QTimer(this)) {
  timer_->setInterval(constants::kTickTime);
  connect(timer_, &QTimer::timeout, this, &Controller::TimerTick);
}

void Controller::TimerTick() {
  model_->ProcessPressedKeys();
}

void Controller::keyPressEvent(QKeyEvent* event) {
  model_->SetPressedKey(event->key());
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  model_->UnsetPressedKey(event->key());
}
