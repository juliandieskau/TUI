#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <Statusbar.hpp>
#include <memory>

using namespace ftxui;
Component Statusbar::displayData() { return container; }

void Statusbar::addField(std::shared_ptr<ECTSPlugin> plugin) {
  auto values = plugin->getImportantValues();
  auto valuesRendered =
      Renderer([=] { return hbox(paragraph(*values)) | hcenter | flex; });
  container->Add(valuesRendered);
};
