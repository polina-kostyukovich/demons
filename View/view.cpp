#include "view.h"

#include <utility>

#include "../Model/constants.h"
#include "../Util/point.h"

View::View() {
  window_width_ = constants::kDefaultWindowWidth;
  window_height_ = constants::kDefaultWindowHeight;
  setBaseSize(window_width_,
               window_height_);
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::paintEvent(QPaintEvent* event) {
  PaintHero();
}

void View::PaintHero() {
  QPainter painter(this);
  Point hero_pos = controller_->GetHero().GetPosition();
  painter.drawEllipse(hero_pos.GetX() - 5,
                      hero_pos.GetY() - 5,
                      10, 10);
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}

int View::GetWindowWidth() const {
  return window_width_;
}

int View::GetWindowHeight() const {
  return window_height_;
}
