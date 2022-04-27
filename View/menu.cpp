#include "menu.h"

#include <QPainter>

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    layout_(new QGridLayout(this)),
    continue_game_(new QPushButton(tr("Continue game"), this)),
    new_game_(new QPushButton(tr("New game"), this)),
    language_(new QComboBox(this)),
    sound_(new QPushButton(tr("Sound"), this)),
    exit_(new QPushButton(tr("Exit"), this)) {
  SetLanguageWidget();
}

void Menu::SetController(
    const std::shared_ptr<AbstractController>& controller) {
  controller_ = controller;
}

void Menu::ConnectWidgets() {
  connect(continue_game_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::ContinueGame);

  connect(new_game_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::StartNewGame);

  connect(language_, &QComboBox::currentIndexChanged, this, [&] {
    controller_->ChangeLanguage(language_->currentIndex());
  });

  connect(sound_,
          &QPushButton::pressed,
          controller_.get(),
          &AbstractController::ChangeSoundOn);

  connect(exit_, &QPushButton::pressed, this, [&] {
    parentWidget()->close();
  });
}

void Menu::SetStyle() {
  SetLayout();
  SetButtonsStyle();
  repaint();
}

void Menu::paintEvent(QPaintEvent*) {
  SetBackground();
}

void Menu::SetBackground() {
  QPainter painter(this);
  QBrush brush(qRgb(240, 240, 240));
  painter.setBrush(brush);
  painter.drawRect(0, 0, width(), height());
}
void Menu::SetLanguageWidget() {
  language_->setPlaceholderText(tr("Choose language"));
  language_->addItem(tr("English"));
  language_->addItem(tr("Russian"));
}
void Menu::SetLayout() {
  layout_->addWidget(sound_, 0, 0, 1, 1, Qt::AlignLeft);
  layout_->addWidget(language_, 0, 1, 1, 2, Qt::AlignLeft);
  layout_->addWidget(exit_, 0, 5, 1, 1, Qt::AlignRight);
  layout_->addWidget(continue_game_, 1, 2, 1, 2, Qt::AlignBottom);
  layout_->addWidget(new_game_, 2, 2, 1, 2, Qt::AlignTop);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 1);
  layout_->setColumnStretch(2, 1);
  layout_->setColumnStretch(3, 1);
  layout_->setColumnStretch(4, 1);
  layout_->setColumnStretch(5, 1);
  setLayout(layout_);
}
void Menu::SetButtonsStyle() {
  sound_->setMinimumSize(40, 40);
  language_->setMinimumSize(120, 40);
  exit_->setMinimumSize(40, 40);
  continue_game_->setMinimumSize(200, 75);
  new_game_->setMinimumSize(200, 75);

  QFont font;
  font.setPixelSize(20);
  sound_->setFont(font);
  language_->setFont(font);
  exit_->setFont(font);

  font.setPixelSize(24);
  continue_game_->setFont(font);
  new_game_->setFont(font);
}
