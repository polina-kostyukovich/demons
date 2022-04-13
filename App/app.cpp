#include "app.h"

#include <cassert>
#include <utility>

void App::Run() {
  view_->show();
}

App::App() {
  std::unique_ptr<Model> model(new Model);
  std::unique_ptr<Controller> controller(new Controller(std::move(model)));
  view_ = std::make_unique<View>(std::move(controller));
}
