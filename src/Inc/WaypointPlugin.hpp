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

class WaypointPlugin : public ECTSPlugin {
    private:
    std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
    std::string name;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    picojson::value waypointlist;
    int current_index;
    int amount_of_waypoints;
    int distance_to_next;
    int total_distance;
    float determineDistance(int index);
    std::string allcontent;
    std::vector<std::shared_ptr<std::string>> important;
    public:
    WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    std::vector<std::shared_ptr<std::string>> getImportantValues();
    Component displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void calculate();
};

#endif //WAYPOINT_PLUGIN_H