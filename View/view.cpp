#include "view.h"

#include <utility>

#include "../Util/point.h"

View::View() {
  setFixedSize(900, 600);
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa1.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa2.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa3.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa4.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa5.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa6.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa5.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa4.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa3.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa2.png"));
  hero_pixmaps_.emplace_back(QPixmap("Picture/Hero/demonessa1.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings1.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings2.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings3.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings4.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings5.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings4.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings3.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings2.png"));
  wings_pixmaps_.emplace_back(QPixmap("Picture/Wings/wings1.png"));
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
  painter.drawPixmap(static_cast<int> (hero_pos.GetX()),
                     static_cast<int>(hero_pos.GetY()),
                     60,
                     60,
                     wings_pixmaps_[controller_->GetTime()
                         % constants::kTickTime * constants::kSlowAnimation
                         % constants::kNumberAnimation]); // бред, пересчитать номер ибо быстро
  // painter.drawPixmap(static_cast<int> (hero_pos.GetX()),
  //                    static_cast<int>(hero_pos.GetY()),
  //                    30,
  //                    30,
  //                    hero_pixmaps_[0]);
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
