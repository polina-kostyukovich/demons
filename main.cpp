#include <QApplication>

#include "App/app.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  std::unique_ptr<Model> model(new Model);
  std::unique_ptr<View> view(new View);
  std::unique_ptr<Controller> controller(new Controller);

  App m_app(std::move(model),
            std::move(view),
            std::move(controller));

  return QApplication::exec();
}
