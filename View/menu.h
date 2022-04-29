#ifndef VIEW_MENU_H_
#define VIEW_MENU_H_

#include <memory>
#include <vector>
#include <QComboBox>
#include <QGridLayout>
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

  void ShowContinueButton();

 private:
  void LoadPictures();

  void SetLanguageWidget();
  void SetLayout();
  void SetButtonsStyle();

 private:
  enum class Sound {
    on,
    off,
  };

 private:
  std::shared_ptr<AbstractController> controller_;

  QGridLayout* layout_;
  QPushButton* continue_game_button_;
  QPushButton* new_game_button_;
  QComboBox* language_combobox_;
  QPushButton* sound_button_;
  QPushButton* exit_button_;

  QPixmap background_picture_;
  QPixmap sound_on_picture_;
  QPixmap sound_off_picture_;
  Sound sound_state_;
};

#endif  // VIEW_MENU_H_
