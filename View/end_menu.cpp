#include "end_menu.h"

#include <QPainter>

EndMenu::EndMenu(QWidget* parent) :
    QWidget(parent),
    to_menu_button_(new QPushButton(tr("To menu"), this)),
    layout_(new QGridLayout(this)) {
  LoadPictures();
  SetLayout();
  SetButtonStyle();
}

void EndMenu::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  switch (mode_) {
    case Mode::kVictory:
      painter.drawPixmap(0, 0, width(), height(), victory_picture_);
      break;
    case Mode::kDefeat:
      painter.drawPixmap(0, 0, width(), height(), defeat_picture_);
  }
}

void EndMenu::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  controller_ = controller;
}

void EndMenu::ConnectButton() {
  connect(to_menu_button_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::ShowMenuAfterEndOfGame);
}

void EndMenu::SetVictoryMode() {
  mode_ = Mode::kVictory;
}

void EndMenu::SetDefeatMode() {
  mode_ = Mode::kDefeat;
}

void EndMenu::LoadPictures() {
  victory_picture_ = QPixmap(":Resources/Picture/Menu/victory.jpg");
  defeat_picture_ = QPixmap(":Resources/Picture/Menu/defeat.jpg");
}

void EndMenu::SetLayout() {
  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 1);
  layout_->setRowStretch(2, 1);
  layout_->setRowStretch(3, 1);
  layout_->setRowStretch(4, 1);
  layout_->setRowStretch(5, 1);

  layout_->addWidget(to_menu_button_, 4, 0, 1, 1, Qt::AlignCenter);
}

void EndMenu::SetButtonStyle() {
  to_menu_button_->setMinimumSize(150, 65);
  QFont font;
  font.setPixelSize(20);
  to_menu_button_->setFont(font);
}
