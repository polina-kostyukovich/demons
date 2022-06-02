#include "view.h"

#include <utility>
#include <QGuiApplication>
#include <QScreen>

View::View() {
  setWindowState(Qt::WindowFullScreen);
  resize(QGuiApplication::primaryScreen()->availableGeometry().size());
  setCentralWidget(&menu_);
  end_menu_.setVisible(false);
  SetIcon();
}

void View::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  assert(controller != nullptr);
  controller_ = controller;
}

void View::CreateMenus() {
  menu_.SetController(controller_);
  menu_.ConnectButtons();
  menu_.SetStyle();

  end_menu_.SetController(controller_);
  end_menu_.ConnectButton();
}

void View::ShowGame() {
  takeCentralWidget();
}

void View::ShowMenu() {
  setCentralWidget(&menu_);
  menu_.ShowContinueButton(true);
  end_menu_.setVisible(false);
}

void View::ShowMenuAfterEndOfGame() {
  takeCentralWidget();
  setCentralWidget(&menu_);
  menu_.ShowContinueButton(false);
  end_menu_.setVisible(false);
}

void View::ShowVictoryEnd() {
  end_menu_.SetVictoryMode();
  end_menu_.setVisible(true);
  setCentralWidget(&end_menu_);
}

void View::ShowDefeatEnd() {
  end_menu_.SetDefeatMode();
  end_menu_.setVisible(true);
  setCentralWidget(&end_menu_);
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
  }

  auto& npc_list = controller_->GetModel().GetNpcController().GetNpcList();
  for (const auto& npc : npc_list) {
    if (npc.GetRenderingLevel() == level) {
      Draw(npc.GetPicture(), painter);
    }
  }

  auto& fireballs = controller_->GetModel().GetFireballs();
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

void View::SetIcon() {
  QPixmap icon(":Resources/Picture/Menu/icon.png");
  setWindowIcon(QIcon(icon));
}
