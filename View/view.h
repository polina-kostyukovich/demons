#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>

#include <QPainter>
#include <QWidget>

#include "../Controller/abstract_controller.h"

class View : public QWidget {
  Q_OBJECT
 public:
  explicit View(std::unique_ptr<AbstractController>&& controller);

  void paintEvent(QPaintEvent* event) override;

  void PaintHero(QPaintEvent* event);

 private:
  std::unique_ptr<AbstractController> controller_;
};

#endif  // VIEW_VIEW_H_
