#include "view.h"

#include <utility>

View::View(std::unique_ptr<AbstractController>&& controller) :
    controller_(std::move(controller)) {}

int View::GetWindowWidth() const {
  // todo
  return 0;
}

int View::GetWindowHeight() const {
  // todo
  return 0;
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}
