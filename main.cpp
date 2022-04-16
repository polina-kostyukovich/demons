#include <QApplication>

#include "App/app.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  std::unique_ptr<Model> model(new Model);
  std::unique_ptr<Controller> controller(new Controller);
  std::shared_ptr<View> view(new View);

  App m_app(std::move(model),
            std::move(controller),
            std::move(view));
  m_app.Run();

  return QApplication::exec();
}
