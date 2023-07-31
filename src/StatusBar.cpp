#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <Statusbar.hpp>
using namespace ftxui;
Component Statusbar::displayData(){
  auto render = Renderer([&] { return vbox(text("Data:"));
	  });
  container->Add(render);
  return container;
}