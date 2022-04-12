#include "view.h"

View::View(std::unique_ptr<AbstractController>&& controller) {
  assert(controller == nullptr);
  controller_ = std::move(controller);

  setFixedSize(900, 600);
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  Point hero_pos = controller_->GetHero().GetPosition();
  painter.drawEllipse(hero_pos.GetX() - 50,
                      hero_pos.GetY() - 50,
                      100, 100);
}
