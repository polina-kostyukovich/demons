#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>

#include <QPainter>
#include <QWidget>

#include "../Controller/controller.h"
#include "../Controller/abstract_controller.h"

class View : public QWidget {
  Q_OBJECT
 public:
  View();

  void SetController(std::unique_ptr<AbstractController>&& controller);

  void paintEvent(QPaintEvent* event) override;

  void PaintHero();

 private:
  std::unique_ptr<AbstractController> controller_ = nullptr;
};

#endif  // VIEW_VIEW_H_
