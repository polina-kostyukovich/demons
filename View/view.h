#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>
#include <QKeyEvent>
#include <QWidget>

#include "../Controller/abstract_controller.h"

class View : public QWidget {
 public:
  explicit View(std::unique_ptr<AbstractController>&& controller);
  int GetWindowWidth() const;
  int GetWindowHeight() const;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  std::unique_ptr<AbstractController> controller_;
};

#endif  // VIEW_VIEW_H_
