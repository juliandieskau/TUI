#ifndef STATUS_BAR_H
#define STATUS_BAR_H
#include "ECTSPlugin.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <memory>

using namespace ftxui;
class Statusbar {
private:
  Component container = Container::Horizontal({});

public:
  Component displayData();
  void addField(std::shared_ptr<ECTSPlugin> plugin);
};
#endif // STATUS_BAR_H