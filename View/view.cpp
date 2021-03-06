#include "view.h"

#include <algorithm>
#include <string>
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
  DrawHeroHealthBar(&painter);
  Draw(GetKnifePicture(), &painter);
  Draw(GetHealthPicture(), &painter);
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
  controller_->WriteSettings();
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

void View::DrawHeroHealthBar(QPainter* painter) {
  painter->save();
  QBrush brush(Qt::SolidPattern);

  long double health_percentage =
      controller_->GetModel().GetHero().GetHealthPoints()
      / constants::kHeroHealthPoints;

  health_percentage = std::max(static_cast<long double> (0), health_percentage);

  QColor color;
  if (health_percentage - 0.5 > constants::kEpsilon) {
    long double red_color = 255 * (1 - health_percentage) * 2;
    color.setRgb(red_color, 255, 0);
  } else {
    long double green_color = 255 * health_percentage * 2;
    color.setRgb(255, green_color, 0);
  }

  brush.setColor(color);
  painter->setBrush(brush);

  long double health_bar_length =
      health_percentage * GetWindowWidth()
      * constants::kHeroHealthBarWidthCoefficient;

  painter->drawRect(constants::kIndentionAlongXAxis,
                    constants::kIndentionAlongYAxis,
                    health_bar_length, constants::kHeroHealthBarHeight);

  brush.setColor(Qt::red);
  painter->setBrush(brush);

  long double progress_percentage =
      static_cast<long double> (controller_->GetModel().GetProgress())
      / constants::kGoalKills;

  progress_percentage =
      std::min(static_cast<long double> (1), progress_percentage);

  long double progress_bar_width =
      GetWindowWidth() * constants::kProgressBarWidthCoefficient
      * progress_percentage;
  painter->drawRect(GetWindowWidth() *
                    (1 - constants::kProgressBarWidthCoefficient
                    - constants::kProgressBarIndentionCoefficient),
                    constants::kIndentionAlongYAxis,
                    progress_bar_width,
                    constants::kProgressBarHeight);
  painter->restore();
}

void View::LoadPictures() {
  std::string way = ":Resources/Picture/StaticObject/Knife.png";
  knife_ = QPixmap(way.c_str());
  way = ":Resources/Picture/StaticObject/Health.png";
  health_ = QPixmap(way.c_str());
}

Picture View::GetHealthPicture() const {
  Picture output;
  output.left_top =
      Point(constants::kHealthKnifeIndention, constants::kHealthKnifeIndention);
  output.picture = health_;
  output.width = constants::kHealthSize;
  output.height = constants::kHealthSize;
  return output;
}

Picture View::GetKnifePicture() const {
  Picture output;
  output.left_top = Point(
      GetWindowWidth() * (1 - constants::kProgressBarWidthCoefficient
          - constants::kProgressBarIndentionCoefficient)
          - constants::kHealthKnifeIndention - constants::kKnifeSize,
      constants::kHealthKnifeIndention);
  output.picture = knife_;
  output.width = constants::kKnifeSize;
  output.height = constants::kKnifeSize;
  return output;
}

void View::SetIcon() {
  QPixmap icon(":Resources/Picture/Menu/icon.png");
  setWindowIcon(QIcon(icon));
}
