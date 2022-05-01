#include "menu.h"

#include <QPainter>

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    layout_(new QGridLayout(this)),
    continue_game_button_(new QPushButton(tr("Continue game"), this)),
    new_game_button_(new QPushButton(tr("New game"), this)),
    settings_button_(new QPushButton(this)),
    exit_button_(new QPushButton(tr("Exit"), this)),
    dropdown_menu_(new QMenu(settings_button_)) {
  LoadPictures();
  continue_game_button_->setVisible(false);
  sound_state_ = Sound::on;
  // in future load from settings
}

void Menu::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  controller_ = controller;
}

void Menu::ConnectButtons() {
  CreateDropdownMenu();
  settings_button_->setMenu(dropdown_menu_);

  connect(continue_game_button_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::StartGame);

  connect(new_game_button_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::NewGame);

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
  settings_picture_ = QPixmap(":Resources/Picture/Menu/settings.png");
  sound_on_picture_ = QPixmap(":Resources/Picture/Menu/sound_on.png");
  sound_off_picture_ = QPixmap(":Resources/Picture/Menu/sound_off.png");
  language_picture_ = QPixmap(":Resources/Picture/Menu/language.png");
}

void Menu::SetLayout() {
  layout_->addWidget(continue_game_button_, 1, 2, 1, 2, Qt::AlignBottom);
  layout_->addWidget(new_game_button_, 2, 2, 1, 2, Qt::AlignTop);
  layout_->addWidget(settings_button_, 3, 4, 1, 1,
                     Qt::AlignVCenter | Qt::AlignRight);
  layout_->addWidget(exit_button_, 3, 5, 1, 1, Qt::AlignCenter);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 1);
  layout_->setColumnStretch(2, 1);
  layout_->setColumnStretch(3, 1);
  layout_->setColumnStretch(4, 1);
  layout_->setColumnStretch(5, 1);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 1);
  layout_->setRowStretch(2, 1);
  layout_->setRowStretch(3, 1);

  setLayout(layout_);
}

void Menu::SetButtonsStyle() {
  settings_button_->setFixedSize(90, 80);
  exit_button_->setFixedSize(90, 80);
  continue_game_button_->setMinimumSize(200, 75);
  new_game_button_->setMinimumSize(200, 75);

  QFont font;
  font.setPixelSize(20);
  exit_button_->setFont(font);

  font.setPixelSize(24);
  continue_game_button_->setFont(font);
  new_game_button_->setFont(font);

  settings_button_->setIcon(QIcon(settings_picture_));
  settings_button_->setIconSize(QSize(70, 70));
}

void Menu::CreateDropdownMenu() {
  QIcon sound_icon;
  if (sound_state_ == Sound::on) {
    sound_icon = QIcon(sound_on_picture_);
  } else {
    sound_icon = QIcon(sound_off_picture_);
  }
  auto sound_action = dropdown_menu_->addAction(sound_icon, tr("Sound"));

  connect(sound_action, &QAction::triggered, this, [&, sound_action] {
    controller_->ChangeSoundOn();
    if (sound_state_ == Sound::on) {
      sound_state_ = Sound::off;
      sound_action->setIcon(QIcon(sound_off_picture_));
    } else {
      sound_state_ = Sound::on;
      sound_action->setIcon(QIcon(sound_on_picture_));
    }
  });

  language_menu_ =
      dropdown_menu_->addMenu(QIcon(language_picture_), tr("Language"));
  auto english_action = language_menu_->addAction(tr("English"));
  auto russian_action = language_menu_->addAction(tr("Russian"));

  connect(english_action, &QAction::triggered, this, [&] {
    controller_->ChangeLanguage(Language::english);
  });
  connect(russian_action, &QAction::triggered, this, [&] {
    controller_->ChangeLanguage(Language::russian);
  });
}
