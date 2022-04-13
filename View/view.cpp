#include "view.h"

#include <utility>

View::View(std::unique_ptr<AbstractController>&& controller) {
  controller_ = std::move(controller);

  setFixedSize(900, 600);
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  PaintHero(&painter);
}

void View::PaintHero(QPainter* painter) {
  Point hero_pos = controller_->GetHero().GetPosition();
  painter->drawEllipse(hero_pos.GetX() - 5,
                      hero_pos.GetY() - 5,
                      10, 10);
}
