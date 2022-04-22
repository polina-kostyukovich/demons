#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>

#include "../Animation/animation.h"
#include "../Controller/abstract_controller.h"

class View : public QWidget {
 public:
  View();

  void SetController(const std::shared_ptr<AbstractController>& controller);

  void paintEvent(QPaintEvent* event) override;

  void PaintHero(QPainter& painter);
  void PaintMap(QPainter& painter);

  int GetWindowWidth() const;
  int GetWindowHeight() const;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  int GetCounter();
  void SetCounter(int i);

 private:
  std::shared_ptr<AbstractController> controller_;
  Animation animation_;
};

#endif  // VIEW_VIEW_H_
