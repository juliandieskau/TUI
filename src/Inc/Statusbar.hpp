#ifndef STATUS_BAR_H
#define STATUS_BAR_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"

using namespace ftxui;
class Statusbar {
private:
	Component container = Container::Horizontal({});
public:
	Component displayData();
	void addField(ECTSPlugin* plugin);
};
#endif //STATUS_BAR_H