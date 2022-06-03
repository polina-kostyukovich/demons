#ifndef VIEW_END_MENU_H_
#define VIEW_END_MENU_H_

#include <memory>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

#include "../Controller/abstract_controller.h"

class EndMenu : public QWidget {
 public:
  explicit EndMenu(QWidget* parent = nullptr);

  void paintEvent(QPaintEvent*) override;

  void SetController(const std::shared_ptr<AbstractController>& controller);
  void ConnectButton();

  void SetVictoryMode();
  void SetDefeatMode();

 private:
  void LoadPictures();
  void SetLayout();
  void SetButtonStyle();

 private:
  enum class Mode {
    kVictory,
    kDefeat,
  };

 private:
  std::shared_ptr<AbstractController> controller_;
  QPushButton* to_menu_button_;
  QGridLayout* layout_;
  QPixmap victory_picture_;
  QPixmap defeat_picture_;
  Mode mode_;
};

#endif  // VIEW_END_MENU_H_
