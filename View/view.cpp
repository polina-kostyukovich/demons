#include "view.h"

#include <utility>

#include "../Util/point.h"

View::View() {
  setWindowState(Qt::WindowFullScreen);
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  PaintMap(&painter);
  PaintHero(&painter);
}

void View::PaintHero(QPainter* painter) {
  Point hero_pos = controller_->GetHero().GetPosition();
  int size = constants::kHeroSize;
  controller_->GetHero().DrawWings(painter, hero_pos, size,
                                   animation_.GetCounter(), &animation_);
  controller_->GetHero().DrawHero(painter, hero_pos, size, &animation_);
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

void View::PaintMap(QPainter* painter) {
  for (int i = 0; i <= GetWindowWidth() / constants::kLavaSize; i++) {
    for (int j = 0; j <= GetWindowHeight() / constants::kLavaSize; j++) {
      painter->drawPixmap(i * constants::kLavaSize, j * constants::kLavaSize,
                          constants::kLavaSize, constants::kLavaSize,
                          animation_.lava);
    }
  }
  for (int i = 0; i <= GetWindowWidth() / constants::kWallSize; i++) {
    painter->drawPixmap(i * constants::kWallSize, 0, constants::kWallSize,
                        constants::kWallSize, animation_.horizontal_wall);
    painter->drawPixmap(i * constants::kWallSize,
                        GetWindowHeight() - constants::kWallSize,
                        constants::kWallSize,
                        constants::kWallSize,
                        animation_.horizontal_wall);
  }
  for (int j = 0; j <= GetWindowHeight() / constants::kWallSize; j++) {
    painter->drawPixmap(0, j * constants::kWallSize, constants::kWallSize,
                        constants::kWallSize, animation_.horizontal_wall);
    painter->drawPixmap(GetWindowWidth() - constants::kWallSize,
                        j * constants::kWallSize,
                        constants::kWallSize,
                        constants::kWallSize,
                        animation_.horizontal_wall);
  }
}

int View::GetCounter() {
  return animation_.GetCounter();
}

void View::SetCounter(int i) {
  animation_.SetCounter(i);
}
