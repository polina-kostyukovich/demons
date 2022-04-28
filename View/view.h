#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <memory>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>

#include "../Controller/abstract_controller.h"
#include "menu.h"
#include "../Util/structs.h"

class View : public QMainWindow {
 public:
  View();

  void SetController(const std::shared_ptr<AbstractController>& controller);
  void CreateMenu();

  void ShowGame();

  void paintEvent(QPaintEvent* event) override;

  void Draw(Picture animation, QPainter* painter);

  int GetWindowWidth() const;
  int GetWindowHeight() const;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  void closeEvent(QCloseEvent* event) override;
  
 private:
  std::shared_ptr<AbstractController> controller_;

  Menu menu_{this};

  int window_width_;
  int window_height_;
};

#endif  // VIEW_VIEW_H_
