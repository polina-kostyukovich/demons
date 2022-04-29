#include "menu.h"

#include <QPainter>
#include <iostream>

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    layout_(new QGridLayout(this)),
    continue_game_button_(new QPushButton(tr("Continue game"), this)),
    new_game_button_(new QPushButton(tr("New game"), this)),
    language_combobox_(new QComboBox(this)),
    sound_button_(new QPushButton(this)),
    exit_button_(new QPushButton(tr("Exit"), this)) {
  SetLanguageWidget();
  LoadPictures();
  continue_game_button_->setVisible(false);

  sound_state_ = Sound::on;
  // in future load from settings
}

void Menu::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  controller_ = controller;
}

void Menu::ConnectWidgets() {
  connect(continue_game_button_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::StartGame);

  connect(new_game_button_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::NewGame);

  connect(language_combobox_, &QComboBox::currentIndexChanged, this, [&] {
    controller_->ChangeLanguage(language_combobox_->currentIndex());
  });

  connect(sound_button_, &QPushButton::pressed, this, [&] {
    controller_->ChangeSoundOn();
    if (sound_state_ == Sound::on) {
      sound_state_ = Sound::off;
      sound_button_->setIcon(QIcon(sound_off_picture_));
    } else {
      sound_state_ = Sound::on;
      sound_button_->setIcon(QIcon(sound_on_picture_));
    }
  });

  connect(exit_button_, &QPushButton::pressed, this, [&] {
    parentWidget()->close();
  });
}

void Menu::SetStyle() {
  SetLayout();
  SetButtonsStyle();
  repaint();
}

void Menu::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, width(), height(), background_picture_);
}

void Menu::ShowContinueButton() {
  continue_game_button_->setVisible(true);
}

void Menu::LoadPictures() {
  background_picture_ = QPixmap(":Resources/Picture/Menu/hell.jpg");
  sound_on_picture_ = QPixmap(":Resources/Picture/Menu/sound_on.png");
  sound_off_picture_ = QPixmap(":Resources/Picture/Menu/sound_off.png");
}

void Menu::SetLanguageWidget() {
  language_combobox_->setPlaceholderText(tr("Choose language"));
  language_combobox_->addItem(tr("English"));
  language_combobox_->addItem(tr("Russian"));
}

void Menu::SetLayout() {
  layout_->addWidget(sound_button_, 0, 0, 1, 1, Qt::AlignCenter);
  layout_->addWidget(language_combobox_, 0, 2, 1, 2, Qt::AlignCenter);
  layout_->addWidget(exit_button_, 0, 5, 1, 1, Qt::AlignCenter);
  layout_->addWidget(continue_game_button_, 1, 2, 1, 2, Qt::AlignBottom);
  layout_->addWidget(new_game_button_, 2, 2, 1, 2, Qt::AlignTop);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 1);
  layout_->setColumnStretch(2, 1);
  layout_->setColumnStretch(3, 1);
  layout_->setColumnStretch(4, 1);
  layout_->setColumnStretch(5, 1);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 1);
  layout_->setRowStretch(2, 1);

  setLayout(layout_);
}
void Menu::SetButtonsStyle() {
  sound_button_->setMinimumSize(90, 90);
  language_combobox_->setMinimumSize(200, 50);
  exit_button_->setMinimumSize(90, 70);
  continue_game_button_->setMinimumSize(200, 75);
  new_game_button_->setMinimumSize(200, 75);

  QFont font;
  font.setPixelSize(20);
  sound_button_->setFont(font);
  language_combobox_->setFont(font);
  exit_button_->setFont(font);

  font.setPixelSize(24);
  continue_game_button_->setFont(font);
  new_game_button_->setFont(font);

  sound_button_->setIcon(QIcon(sound_on_picture_));
  sound_button_->setIconSize(QSize(70, 70));
}
