#include "view.h"

#include <utility>
#include <QGuiApplication>
#include <QScreen>

View::View() {
  setWindowState(Qt::WindowFullScreen);
  resize(QGuiApplication::primaryScreen()->availableGeometry().size());
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  Draw(controller_->GetMap().GetPicture(), &painter);
  Draw(controller_->GetHero().GetPicture(controller_->GetCounter()),
       &painter);
  std::vector<Fireball> fireballs = controller_->GetModel()->GetFireballs();
  for (auto fireball : fireballs) {
    painter.drawEllipse(fireball.GetPosition().GetX() - 15, fireball.GetPosition().GetY() - 15,
                        30, 30);
  }
}

void View::Draw(Picture animation, QPainter* painter) {
  painter->drawPixmap(static_cast<int>(animation.left_top.GetX()),
                      static_cast<int>(animation.left_top.GetY()),
                      animation.width,
                      animation.height,
                      animation.picture);
}

int View::GetWindowWidth() const {
  return window()->width();
}

int View::GetWindowHeight() const {
  return window()->height();
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}

void View::mousePressEvent(QMouseEvent *event) {
  Point mouse_pos = {static_cast<long double>(cursor().pos().x()),
                     static_cast<long double>(cursor().pos().y())};
  controller_->HandleMousePressEvent(event, mouse_pos);
}

void View::mouseReleaseEvent(QMouseEvent *event) {
  controller_->HandleMouseReleaseEvent(event);
}
