#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <Statusbar.hpp>

using namespace ftxui;
Component Statusbar::displayData() {
  return container;
}
void Statusbar::addField(std::shared_ptr<ECTSPlugin> plugin) {
  auto values = plugin.getImportantValues();
  std::string all = "";
  for (int i = 0; i < values.size(); i++) {
    all = all + *values[i] + " ";
  }
  auto render = Renderer([&] { return hbox(text(all));
	  });
  container->Add(render);
};
