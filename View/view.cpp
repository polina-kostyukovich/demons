#include "view.h"

#include <algorithm>
#include <utility>
#include <QGuiApplication>
#include <QScreen>

View::View() {
  setWindowState(Qt::WindowFullScreen);
  resize(QGuiApplication::primaryScreen()->availableGeometry().size());
  setCentralWidget(&menu_);
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::CreateMenu() {
  menu_.SetController(controller_);
  menu_.ConnectButtons();
  menu_.SetStyle();
}

void View::ShowGame() {
  takeCentralWidget();
}

void View::ShowMenu() {
  setCentralWidget(&menu_);
  menu_.ShowContinueButton();
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  Draw(controller_->GetModel().GetMap().GetPicture(), &painter);

  int max_rendering_level = controller_->GetMaxRenderingLevel();
  for (int level = 0; level <= max_rendering_level; ++level) {
    RenderLevel(level, &painter);
  }
  DrawHeroHealthBar(&painter);
}

void View::Draw(const Picture& animation, QPainter* painter) {
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

void View::closeEvent(QCloseEvent* event) {
  // save settings
}

void View::mousePressEvent(QMouseEvent* event) {
  controller_->HandleMousePressEvent(event);
}

void View::RenderLevel(int level, QPainter* painter) {
  if (controller_->GetModel().GetHero().GetRenderingLevel() == level) {
    Draw(controller_->GetModel().GetHero().GetPicture(
        controller_->GetCounter()),
         painter);
  }

  auto npc_list = controller_->GetModel().GetNpcController().GetNpcList();
  for (const auto& npc : npc_list) {
    if (npc.GetRenderingLevel() == level) {
      Draw(npc.GetPicture(), painter);
    }
  }

  auto fireballs = controller_->GetModel().GetFireballs();
  for (const auto& fireball : fireballs) {
    if (fireball.GetRenderingLevel() == level) {
      Draw(fireball.GetPicture(), painter);
    }
  }

  for (const auto& object : controller_->GetModel().GetMap().GetObjects()) {
    if (object->GetRenderingLevel() == level) {
      Draw(object->GetPicture(), painter);
    }
  }
}

void View::DrawHeroHealthBar(QPainter* painter) {
  QBrush brush(Qt::SolidPattern);
  brush.setColor(Qt::green);
  painter->setBrush(brush);

  long double health_percentage =
      controller_->GetModel().GetHero().GetHealthPoints();
  health_percentage /= constants::kHeroHealthPoints;

  health_percentage = std::max(static_cast<long double> (0), health_percentage);

  long double health_bar_length =
      health_percentage * constants::kHeroHealthBarWidth;

  painter->drawRect(0, 0, health_bar_length, constants::kHeroHealthBarHeight);
}
