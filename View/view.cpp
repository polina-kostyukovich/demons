#include "view.h"

View::View() {
  setFixedSize(900, 600);
}

void View::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
}
