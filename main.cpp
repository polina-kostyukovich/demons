#include <QApplication>

#include "App/app.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  App m_app;
  m_app.Run();

  return QApplication::exec();
}
