#include "end_menu.h"

EndMenu::EndMenu(QWidget* parent) :
    QWidget(parent),
    to_menu_button_(new QPushButton(tr("To menu"), this)),
    layout_(new QGridLayout(this)) {
  LoadPictures();
  SetLayout();
  ConnectButton();
  SetButtonStyle();
}

void EndMenu::paintEvent(QPaintEvent*) {

}

void EndMenu::LoadPictures() {
  victory_picture_ = QPixmap(":Resources/Picture/Menu/victory.jpg");
  defeat_picture_ = QPixmap(":Resources/Picture/Menu/defeat.jpg");
}

void EndMenu::SetLayout() {

}

void EndMenu::ConnectButton() {

}

void EndMenu::SetButtonStyle() {

}
