#ifndef BATTERY_PLUGIN_H
#define BATTERY_PLUGIN_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"
using namespace ftxui;
class BatteryPlugin {
    public:
    BatteryPlugin(rosbridge_client_cpp::RosbridgeClient rb);
    private:
    rosbridge_client_cpp::RosbridgeClient ros;
};
#endif //BATTERY_PLUGIN_H