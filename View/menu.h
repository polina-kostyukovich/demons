#ifndef VIEW_MENU_H_
#define VIEW_MENU_H_

#include <memory>
#include <QGridLayout>
#include <QMenu>
#include <QPushButton>
#include <QWidget>

#include "../Controller/abstract_controller.h"
#include "../Model/constants.h"
#include "../Util/structs.h"

class Menu : public QWidget {
 public:
  explicit Menu(QWidget* parent = nullptr);
  void SetController(const std::shared_ptr<AbstractController>& controller_);

  void ConnectButtons();
  void SetStyle();

  void paintEvent(QPaintEvent*) override;

  void ShowContinueButton(bool is_visible);

 private:
  void LoadPictures();

  void SetLayout();
  void SetButtonsStyle();

  void CreateDropdownMenu();

 private:
  enum class Sound {
    kOn,
    kOff,
  };

 private:
  std::shared_ptr<AbstractController> controller_;

  QGridLayout* layout_;
  QPushButton* continue_game_button_;
  QPushButton* new_game_button_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  QMenu* dropdown_menu_;
  QMenu* language_menu_;

  QPixmap background_picture_;
  QPixmap settings_picture_;
  QPixmap sound_on_picture_;
  QPixmap sound_off_picture_;
  QPixmap language_picture_;
  Sound sound_state_;
};

#endif  // VIEW_MENU_H_
