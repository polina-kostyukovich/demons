#include "app.h"

#include <utility>

App::App(std::shared_ptr<Model>&& model,
    std::shared_ptr<Controller>&& controller,
    std::unique_ptr<View>&& view) {
  assert(model != nullptr && controller != nullptr && view != nullptr);
  controller_ = std::move(controller);

  view->SetController(controller_);
  controller_->SetModel(std::move(model));
  controller_->SetView(std::move(view));
  controller_->ConnectTimer();
}

void App::Run() {
  controller_->Start();
}
