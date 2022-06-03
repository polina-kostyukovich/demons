#include "menu.h"

#include <QPainter>

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    layout_(new QGridLayout(this)),
    continue_game_button_(new QPushButton(tr(""), this)),
    new_game_button_(new QPushButton(tr(""), this)),
    settings_button_(new QPushButton(this)),
    exit_button_(new QPushButton(tr(""), this)),
    dropdown_menu_(new QMenu(settings_button_)) {
  LoadPictures();
  continue_game_button_->setVisible(false);
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

void Menu::ShowContinueButton(bool is_visible) {
  continue_game_button_->setVisible(is_visible);
}

void Menu::LoadPictures() {
  background_picture_ = QPixmap(":Resources/Picture/Menu/hell.jpg");
  sound_on_picture_ = QPixmap(":Resources/Picture/Menu/sound_on.png");
  sound_off_picture_ = QPixmap(":Resources/Picture/Menu/sound_off.png");
  language_picture_ = QPixmap(":Resources/Picture/Menu/language.png");
}

void Menu::SetLayout() {
  layout_->addWidget(continue_game_button_, 1, 3, 1, 2, Qt::AlignBottom);
  layout_->addWidget(new_game_button_, 2, 3, 1, 2, Qt::AlignTop);
  layout_->addWidget(settings_button_, 3, 5, 1, 1,
                     Qt::AlignVCenter | Qt::AlignRight);
  layout_->addWidget(exit_button_, 3, 6, 1, 1, Qt::AlignCenter);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 1);
  layout_->setColumnStretch(2, 1);
  layout_->setColumnStretch(3, 1);
  layout_->setColumnStretch(4, 1);
  layout_->setColumnStretch(5, 1);
  layout_->setColumnStretch(6, 1);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 1);
  layout_->setRowStretch(2, 1);
  layout_->setRowStretch(3, 1);

  setLayout(layout_);
}

void Menu::SetButtonsStyle() {
  settings_button_->setFixedSize(90, 80);
  exit_button_->setFixedSize(90, 80);

  new_game_button_->setFixedSize(parentWidget()->width() / 7, 75);
  QPixmap img(":Resources/Picture/Menu/start_button.png");
  new_game_button_->setIcon(QIcon(img));
  new_game_button_->setIconSize({parentWidget()->width() / 7, 75});

  QPixmap img2(":Resources/Picture/Menu/continue_button.png");
  continue_game_button_->setFixedSize(parentWidget()->width() / 7, 75);
  continue_game_button_->setIcon(QIcon(img2));
  continue_game_button_->setIconSize({parentWidget()->width() / 7, 75});

  QPixmap img3(":Resources/Picture/Menu/exit_button.png");
  exit_button_->setIcon(QIcon(img3));
  exit_button_->setIconSize({100, 90});

  QPixmap img4(":Resources/Picture/Menu/settings_button.png");
  settings_button_->setIcon(QIcon(img4));
  settings_button_->setIconSize({90, 80});

  QFont font;
  font.setPixelSize(20);
  exit_button_->setFont(font);

  font.setPixelSize(24);
  continue_game_button_->setFont(font);
  new_game_button_->setFont(font);
}

void Menu::CreateDropdownMenu() {
  QIcon sound_icon;
  if (controller_->IsSoundOn()) {
    sound_icon = QIcon(sound_on_picture_);
  } else {
    sound_icon = QIcon(sound_off_picture_);
  }
  auto sound_action = dropdown_menu_->addAction(sound_icon, tr("Sound"));

  connect(sound_action, &QAction::triggered, this, [&, sound_action] {
    controller_->ChangeSoundOn();
    if (controller_->IsSoundOn()) {
      sound_action->setIcon(QIcon(sound_on_picture_));
    } else {
      sound_action->setIcon(QIcon(sound_off_picture_));
    }
  });

  language_menu_ =
      dropdown_menu_->addMenu(QIcon(language_picture_), tr("Language"));
  auto english_action = language_menu_->addAction(tr("English"));
  auto russian_action = language_menu_->addAction(tr("Russian"));

  connect(english_action, &QAction::triggered, this, [&] {
    controller_->ChangeLanguage(Language::kEnglish);
  });
  connect(russian_action, &QAction::triggered, this, [&] {
    controller_->ChangeLanguage(Language::kRussian);
  });
}
