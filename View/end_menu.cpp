#include "end_menu.h"

EndMenu::EndMenu(QWidget* parent) :
    QWidget(parent),
    to_menu_button_(new QPushButton(tr("To menu"), this)),
    layout_(new QGridLayout(this)) {
  LoadPictures();
  SetLayout();
  ConnectButton();
  SetStyle();
}

void EndMenu::paintEvent(QPaintEvent*) {

}

void EndMenu::LoadPictures() {

}

void EndMenu::SetLayout() {

}

void EndMenu::ConnectButton() {

}

void EndMenu::SetStyle() {

}
