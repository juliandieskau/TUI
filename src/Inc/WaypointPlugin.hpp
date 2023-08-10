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
    std::vector<picojson::value> waypointlist;
    int current_index;
    int amount_of_waypoints;
    float distance_to_next;
    float total_distance;
    float determineDistance(int index);
    std::string allcontent;
    std::shared_ptr<std::string> important;
    rosbridge_client_cpp::Subscriber* waypointlistsub;
    rosbridge_client_cpp::Subscriber* numwaypointsub;
    rosbridge_client_cpp::Subscriber* currentpointsub;
    bool isLoaded();
  
  public:
    WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    std::shared_ptr<std::string> getImportantValues();
    Component displayData();
    void subscribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void calculate();
    bool loaded = false;
};

#endif //WAYPOINT_PLUGIN_H