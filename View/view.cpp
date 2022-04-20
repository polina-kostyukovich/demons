#include "view.h"

#include <utility>

#include "../Util/point.h"

View::View() {
  setFixedSize(900, 600);
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
  int number_animation = (controller_->GetTime() / constants::kTickTime)
      % (constants::kSlowAnimation
          * constants::kNumberAnimation)
      / constants::kNumberAnimation;
  painter.drawPixmap(static_cast<int> (hero_pos.GetX()),
                     static_cast<int>(hero_pos.GetY()), 60, 60,
                     animation_.wings_pixmaps_[number_animation]);
  painter.drawPixmap(static_cast<int> (hero_pos.GetX()),
                     static_cast<int>(hero_pos.GetY()), 60, 60,
                     animation_.hero_pixmaps_[number_animation]);
  // painter.drawEllipse(hero_pos.GetX() - 5,
  //                     hero_pos.GetY() - 5,
  //                     10, 10);
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}

int View::GetWindowWidth() const {
  // todo
  return 900;
}

int View::GetWindowHeight() const {
  // todo
  return 600;
}
