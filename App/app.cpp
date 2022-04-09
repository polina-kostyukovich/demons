#include "app.h"

#include <cassert>
#include <utility>

App::App(std::unique_ptr<Model>&& model,
         std::unique_ptr<View>&& view,
         std::unique_ptr<Controller>&& controller) {
  assert(model_ == nullptr && view_ == nullptr && controller_ == nullptr);

  model_ = std::move(model);
  view_ = std::move(view);
  controller_ = std::move(controller);

  view_->show();
}

void App::Run() {
}

