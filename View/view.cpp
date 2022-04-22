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
  QPainter painter(this);
  PaintMap(painter);
  PaintHero(painter);
}

void View::PaintHero(QPainter& painter) {
  Point hero_pos = controller_->GetHero().GetPosition();
  int size = constants::kHeroSize * GetWindowHeight()
      / constants::kStandartHeight; // чтобы герой увеличивался при ресайзе
  animation_.wings_.DrawWings(&painter, hero_pos, size, animation_.counter_);
  animation_.hero_animation_.DrawHero(&painter, hero_pos, size);
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}

int View::GetWindowWidth() const {
  return window()->width();
}

int View::GetWindowHeight() const {
  return window()->height();
}

void View::PaintMap(QPainter& painter) {
  painter.drawTiledPixmap(0, 0, GetWindowWidth(), GetWindowHeight(),
                          animation_.lava);

  painter.drawTiledPixmap(0, 0, GetWindowWidth(), constants::kWallSize,
                          animation_.horizontal_wall);
  painter.drawTiledPixmap(0, GetWindowHeight() - constants::kWallSize,
                          GetWindowWidth(), constants::kWallSize,
                          animation_.horizontal_wall);

  painter.drawTiledPixmap(0, 0, constants::kWallSize, GetWindowHeight(),
                          animation_.vertical_wall);
  painter.drawTiledPixmap(GetWindowWidth() - constants::kWallSize, 0,
                          GetWindowWidth(), GetWindowHeight(),
                          animation_.vertical_wall);
}

int View::GetCounter() {
  return animation_.GetCounter();
}

void View::SetCounter(int i) {
  animation_.SetCounter(i);
}
