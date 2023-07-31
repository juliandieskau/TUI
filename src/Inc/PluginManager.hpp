#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;
// Fügt der TUI die Checkboxen hinzu und managed visibility der Plugins
class PluginManager {
private:
	Component container;
public:
    PluginManager();
	Component displayData();
	void addCheckbox(Component check);
};
#endif //PLUGIN_MANAGER_H