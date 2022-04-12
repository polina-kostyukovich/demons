#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QPainter>
#include <QWidget>

class View : public QWidget {
  Q_OBJECT
 public:
  View();

  void paintEvent(QPaintEvent *event);

 private:
};

#endif  // VIEW_VIEW_H_
