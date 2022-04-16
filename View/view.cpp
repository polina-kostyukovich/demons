#include "view.h"

#include <utility>

#include "../Util/point.h"

View::View() {
  setFixedSize(900, 600);
}

void View::SetController(std::unique_ptr<AbstractController>&& controller) {
  assert(controller != nullptr);
  controller_ = std::move(controller);
}

void View::Start() {
  controller_->StartTimer();
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
  // todo
  return 900;
}

int View::GetWindowHeight() const {
  // todo
  return 600;
}
