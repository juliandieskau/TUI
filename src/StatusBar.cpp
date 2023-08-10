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
void Statusbar::addField(ECTSPlugin* plugin) {
  auto values = (*(plugin)).getImportantValues();
  auto render = Renderer([=] { return hbox(paragraph(*values));});
  container->Add(render);
};
