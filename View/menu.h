#ifndef VIEW_MENU_H_
#define VIEW_MENU_H_

#include <memory>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

#include "../Controller/abstract_controller.h"
#include "../Model/constants.h"

class Menu : public QWidget {
 public:
  explicit Menu(QWidget* parent = nullptr);
  void SetController(const std::shared_ptr<AbstractController>& controller_);

  void ConnectWidgets();
  void SetStyle();

  void paintEvent(QPaintEvent*) override;

 private:
  void SetBackground();
  void SetLanguageWidget();
  void SetLayout();
  void SetButtonsStyle();

 private:
  std::shared_ptr<AbstractController> controller_;

  QGridLayout* layout_;
  QPushButton* continue_game_;
  QPushButton* new_game_;
  QComboBox* language_;
  QPushButton* sound_;
  QPushButton* exit_;
};

#endif  // VIEW_MENU_H_
