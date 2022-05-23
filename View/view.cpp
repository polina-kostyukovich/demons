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

  int max_rendering_level = controller_->GetMaxRenderingLevel();
  for (int level = 0; level <= max_rendering_level; ++level) {
    RenderLevel(level, &painter);
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

void View::RenderLevel(int level, QPainter* painter) {
  if (controller_->GetModel().GetHero().GetRenderingLevel() == level) {
    Draw(controller_->GetModel().GetHero().GetPicture(
        controller_->GetCounter()),
         painter);
    painter->drawRect(
        controller_->GetModel().GetHero().GetPosition().GetX()
        - controller_->GetModel().GetHero().GetHitBox().GetWidth() / 2,
        controller_->GetModel().GetHero().GetPosition().GetY()
        - controller_->GetModel().GetHero().GetHitBox().GetHeight() / 2
        + controller_-> GetModel().GetHero().GetHitBox().GetVerticalShift(),
        controller_->GetModel().GetHero().GetHitBox().GetWidth(),
        controller_->GetModel().GetHero().GetHitBox().GetHeight());

    painter->drawRect(
        controller_->GetModel().GetHero().GetPosition().GetX()
            - controller_->
            GetModel().GetHero().GetPictureAboveHitBox().GetWidth() / 2,
        controller_->GetModel().GetHero().GetPosition().GetY()
            - controller_->
            GetModel().GetHero().GetPictureAboveHitBox().GetHeight() / 2
            + controller_->
            GetModel().GetHero().GetPictureAboveHitBox().GetVerticalShift(),
        controller_->GetModel().GetHero().GetPictureAboveHitBox().GetWidth(),
        controller_->GetModel().GetHero().GetPictureAboveHitBox().GetHeight());
  }

  auto npc_list = controller_->GetModel().GetNpcController().GetNpcList();
  for (const auto& npc : npc_list) {
    if (npc.GetRenderingLevel() == level) {
      Draw(npc.GetPicture(), painter);
      painter->drawRect(npc.GetPosition().GetX()
                        - npc.GetHitBox().GetWidth() / 2,
                       npc.GetPosition().GetY()
                        - npc.GetHitBox().GetHeight() / 2
                        + npc.GetHitBox().GetVerticalShift(),
                       npc.GetHitBox().GetWidth(), npc.GetHitBox().GetHeight());
      painter->drawRect(npc.GetPosition().GetX()
                            - npc.GetPictureAboveHitBox().GetWidth() / 2,
                        npc.GetPosition().GetY()
                            - npc.GetPictureAboveHitBox().GetHeight() / 2
                            + npc.GetPictureAboveHitBox().GetVerticalShift(),
                        npc.GetPictureAboveHitBox().GetWidth(),
                        npc.GetPictureAboveHitBox().GetHeight());
    }
  }

  auto fireballs = controller_->GetModel().GetFireballs();
  for (const auto& fireball : fireballs) {
    if (fireball.GetRenderingLevel() == level) {
      Draw(fireball.GetPicture(), painter);
      painter->drawRect(fireball.GetPosition().GetX()
                        - fireball.GetHitBox().GetWidth() / 2,
                        fireball.GetPosition().GetY()
                        - fireball.GetHitBox().GetHeight() / 2
                        + fireball.GetHitBox().GetVerticalShift(),
                        fireball.GetHitBox().GetWidth(),
                        fireball.GetHitBox().GetHeight());
    }
  }

  for (const auto& object : controller_->GetModel().GetMap().GetObjects()) {
    if (object->GetRenderingLevel() == level) {
      Draw(object->GetPicture(), painter);
      painter->drawRect(object->GetPosition().GetX() -
                            object->GetHitBox().GetWidth() / 2,
                        object->GetPosition().GetY()
                            - object->GetHitBox().GetHeight() / 2
                            + object->GetHitBox().GetVerticalShift(),
                        object->GetHitBox().GetWidth(),
                        object->GetHitBox().GetHeight());

      painter->drawRect(object->GetPosition().GetX() -
                            object->GetPictureAboveHitBox().GetWidth() / 2,
                        object->GetPosition().GetY()
                            - object->GetPictureAboveHitBox().GetHeight() / 2
                            + object->GetPictureAboveHitBox().
                            GetVerticalShift(),
                        object->GetPictureAboveHitBox().GetWidth(),
                        object->GetPictureAboveHitBox().GetHeight());
    }
  }
}
