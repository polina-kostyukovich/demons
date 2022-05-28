#ifndef APP_APP_H_
#define APP_APP_H_

#include <memory>

#include "../Controller/controller.h"
#include "../Model/model.h"
#include "../View/view.h"

class App {
 public:
  App(std::shared_ptr<Model>&& model,
      std::shared_ptr<Controller>&& controller,
      std::unique_ptr<View>&& view);
  void Run();

 private:
  std::shared_ptr<Controller> controller_;
};

#endif  // APP_APP_H_
