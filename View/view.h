#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>

#include "../Controller/abstract_controller.h"
#include "../Util/structs.h"

class View : public QWidget {
 public:
  View();

  void SetController(const std::shared_ptr<AbstractController>& controller);

  void paintEvent(QPaintEvent* event) override;

  void Draw(Picture animation, QPainter* painter);

  int GetWindowWidth() const;
  int GetWindowHeight() const;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

 private:
  std::shared_ptr<AbstractController> controller_;

  int window_width_;
  int window_height_;
};

#endif  // VIEW_VIEW_H_
