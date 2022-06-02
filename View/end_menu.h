#ifndef VIEW_END_MENU_H_
#define VIEW_END_MENU_H_

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class EndMenu : public QWidget {
 public:
  explicit EndMenu(QWidget* parent = nullptr);

  void paintEvent(QPaintEvent*) override;

 private:
  void LoadPictures();
  void SetLayout();
  void ConnectButton();
  void SetStyle();

 private:
  QPushButton* to_menu_button_;
  QGridLayout* layout_;
  QPixmap victory_picture_;
  QPixmap defeat_picture_;
};

#endif  // VIEW_END_MENU_H_
