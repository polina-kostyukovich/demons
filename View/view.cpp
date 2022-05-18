#include "view.h"

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
//  painter.drawRect(controller_->GetModel().GetHero().GetPosition().GetX()
//                   - controller_->GetModel().GetHero().GetHitBox().GetWidth()
//                   / 2,
//                   controller_->GetModel().GetHero().GetPosition().GetY()
//                   - controller_->GetModel().GetHero().GetHitBox().GetHeight()
//                   / 2
//                   + controller_->
//                   GetModel().GetHero().GetHitBox().GetVerticalShift(),
//                   controller_->GetModel().GetHero().GetHitBox().GetWidth(),
//                   controller_->GetModel().GetHero().GetHitBox().GetHeight());

  for (const auto& object : controller_->GetModel().GetMap().GetObjects()) {
    Draw(object->GetPicture(), &painter);
//    painter.drawRect(object->GetPosition().GetX() -
//                    object->GetHitBox().GetWidth() / 2,
//                    object->GetPosition().GetY()
//                    - object->GetHitBox().GetHeight() / 2
//                    + object->GetHitBox().GetVerticalShift(),
//                    object->GetHitBox().GetWidth(),
//                    object->GetHitBox().GetHeight());
  }

  auto npc_list = controller_->GetModel().GetNpcController().GetNpcList();
  for (const auto& npc : npc_list) {
//    painter.drawRect(npc.GetPosition().GetX() - npc.GetHitBox().GetWidth() / 2,
//                     npc.GetPosition().GetY() - npc.GetHitBox().GetHeight() / 2
//                     + npc.GetHitBox().GetVerticalShift(),
//                     npc.GetHitBox().GetWidth(), npc.GetHitBox().GetHeight());
    Draw(npc.GetPicture(), &painter);
  }

  Draw(controller_->GetModel().GetHero().GetPicture(controller_->GetCounter()),
       &painter);

  auto fireballs = controller_->GetModel().GetFireballs();
  for (const auto& fireball : fireballs) {
    Draw(fireball.GetPicture(), &painter);
  }

  for (const auto& object : controller_->GetModel().GetMap().GetObjects()) {
    if (object->IsOverSomething()) {
      Draw(object->GetPicture(), &painter);
    }
  }
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
