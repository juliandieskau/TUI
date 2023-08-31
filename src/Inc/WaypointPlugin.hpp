#ifndef WAYPOINT_PLUGIN_H
#define WAYPOINT_PLUGIN_H

#include "ECTSPlugin.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "rosbridge_client_cpp/rosbridge.h"
#include <cmath>
#include <memory>

using namespace ftxui;

class WaypointPlugin : public ECTSPlugin {
private:
  std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
  std::string name;
  std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
  std::vector<picojson::value> waypointlist{};
  int current_index{};
  int amount_of_waypoints{};
  float distance_to_next{};
  float total_distance{};
  float determineDistance(int index);
  std::vector<Element> allvaltotal{};
  std::shared_ptr<std::string> important;
  rosbridge_client_cpp::Subscriber *waypointlistsub;
  rosbridge_client_cpp::Subscriber *numwaypointsub;
  rosbridge_client_cpp::Subscriber *currentpointsub;
  bool isLoaded();
  int maxwidth = 5;
  std::string truncate(std::string str);

public:
  WaypointPlugin(std::string name,
                 std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
  void sendMessage();
  std::shared_ptr<std::string> getImportantValues();
  Component displayData();
  void subscribeToROS();
  std::string getName();
  void unsubscribeFromROS();
  void calculate();
  bool loaded = false;

  std::tuple<double, double> position(int index);
};

#endif // WAYPOINT_PLUGIN_H