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
#include <cmath>

using namespace ftxui;
class WaypointPlugin {
    private:
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    std::value waypointlist;
    int current_index;
    int amount_of_waypoints;
    int distance_to_next;
    int total_distance;
    float determineDistance(int index);
    std::string allcontent;
    public:
    WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    Component displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void update();
    bool* getshown();
    std::string getboolean();
    void calculate();
};
#endif //WAYPOINT_PLUGIN_H