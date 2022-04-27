#include "view.h"

#include <utility>

#include "../Model/constants.h"
#include "../Util/point.h"

View::View() {
  window_width_ = constants::kDefaultWindowWidth;
  window_height_ = constants::kDefaultWindowHeight;
  setMinimumSize(window_width_, window_height_);

  setCentralWidget(&menu_);
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::CreateMenu() {
  menu_.SetController(controller_);
  menu_.ConnectWidgets();
  menu_.SetStyle();
}

void View::ShowGame() {
  takeCentralWidget();
  menu_.setVisible(false);
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

int View::GetWindowWidth() const {
  return window_width_;
}

int View::GetWindowHeight() const {
  return window_height_;
}

void View::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}
void View::resizeEvent(QResizeEvent* event) {
  window_width_ = event->size().width();
  window_height_ = event->size().height();
}

void View::closeEvent(QCloseEvent* event) {
  // save settings
}
