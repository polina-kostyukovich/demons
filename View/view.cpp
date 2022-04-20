#include "view.h"

#include <utility>

#include "../Util/point.h"

View::View() {
  setFixedSize(900, 600);
  QPainter painter(this);
  for (int i = 0; i <= window()->width() / constants::kLavaSize; i++) {
    for (int j = 0; j <= window()->height() / constants::kLavaSize; j++) {
      painter.drawPixmap(i * constants::kLavaSize, j * constants::kLavaSize,
                         constants::kLavaSize, constants::kLavaSize,
                         animation_.lava);
    }
    painter.drawPixmap(i * constants::kWallSize, 0, constants::kWallSize,
                       constants::kWallSize, animation_.horizontal_wall);
    painter.drawPixmap(i * constants::kWallSize,
                       window()->height() - constants::kWallSize,
                       constants::kWallSize,
                       constants::kWallSize,
                       animation_.horizontal_wall);
  }
  for (int j = 0; j <= window()->height() / constants::kWallSize; j++) {
    painter.drawPixmap(0, j * constants::kWallSize, constants::kWallSize,
                       constants::kWallSize, animation_.horizontal_wall);
    painter.drawPixmap(window()->width() - constants::kWallSize,
                       j * constants::kWallSize,
                       constants::kWallSize,
                       constants::kWallSize,
                       animation_.horizontal_wall);
  }
}

void View::SetController(
    const std::shared_ptr <AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::paintEvent(QPaintEvent* event) {
  PaintHero();
}

void View::PaintHero() {
  QPainter painter(this);
  Point hero_pos = controller_->GetHero().GetPosition();
  int number_animation = ((controller_->GetTime() / constants::kTickTime)
      % (constants::kSlowAnimation * constants::kNumberAnimation))
      / constants::kSlowAnimation;
  painter.drawPixmap(static_cast<int> (hero_pos.GetX()) - 5,
                     static_cast<int>(hero_pos.GetY()) - 5,
                     constants::kHeroSize * window()->height()
                         / constants::kStandartHeight,
                     constants::kHeroSize * window()->height()
                         / constants::kStandartHeight,
                     animation_.wings_pixmaps[number_animation]);
  painter.drawPixmap(static_cast<int> (hero_pos.GetX()) - 5,
                     static_cast<int>(hero_pos.GetY()) - 5, 60, 60,
                     animation_.hero_pixmaps[number_animation]);
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
