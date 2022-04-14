#include "app.h"

#include <utility>

App::App(std::unique_ptr<Model>&& model,
    std::unique_ptr<Controller>&& controller,
    std::unique_ptr<View>&& view) {
  assert(model != nullptr && controller != nullptr && view != nullptr);
  view_ = std::move(view);

  controller->SetModel(std::move(model));
  view_->SetController(std::move(controller));
}

void App::Run() {
  view_->show();
}
