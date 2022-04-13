#ifndef APP_APP_H_
#define APP_APP_H_

#include <memory>

#include "../Controller/controller.h"
#include "../Model/model.h"
#include "../View/view.h"

class App {
 public:
  App();
  void Run();

 private:
  std::unique_ptr<View> view_ = nullptr;
};

#endif  // APP_APP_H_
