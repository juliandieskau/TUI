#ifndef WAYPOINT_PLUGIN_H
#define WAYPOINT_PLUGIN_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;
class WaypointPlugin {
    private:
    rosbridge_client_cpp::RosbridgeClient ros;
    public:
    WaypointPlugin(rosbridge_client_cpp::RosbridgeClient rb);
};
#endif //WAYPOINT_PLUGIN_H