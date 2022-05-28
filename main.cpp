#include <QApplication>

#include "App/app.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  std::shared_ptr<Model> model(new Model);
  std::shared_ptr<Controller> controller(new Controller);
  std::unique_ptr<View> view(new View);

  App m_app(std::move(model),
            std::move(controller),
            std::move(view));
  m_app.Run();

  return QApplication::exec();
}
