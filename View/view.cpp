#include "view.h"

#include <utility>

View::View(std::unique_ptr<AbstractController>&& controller) {
  assert(controller != nullptr);
  controller_ = std::move(controller);

  setFixedSize(900, 600);
}

void View::paintEvent(QPaintEvent* event) {
  PaintHero(event);
}

void View::PaintHero(QPaintEvent* event) {
  QPainter painter(this);
  Point hero_pos = controller_->GetHero().GetPosition();
  painter.drawEllipse(hero_pos.GetX() - 5,
                      hero_pos.GetY() - 5,
                      10, 10);
}
