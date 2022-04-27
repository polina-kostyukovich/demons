#include "view.h"

#include <utility>

View::View() {
  QWidget::showFullScreen();
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  Draw(controller_->GetMap().GetAnimation(), &painter);
  Draw(controller_->GetHero().GetAnimation(controller_->GetCounter()),
       &painter);
}

void View::Draw(Animation animation, QPainter* painter) {
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
