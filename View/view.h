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

  void PaintHero();
  void PaintMap();

  int GetWindowWidth() const;
  int GetWindowHeight() const;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  std::shared_ptr<AbstractController> controller_;

 public:
  Animation animation_;
};

#endif  // VIEW_VIEW_H_
