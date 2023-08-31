#ifndef BATTERY_PLUGIN_H
#define BATTERY_PLUGIN_H

#include "ECTSPlugin.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "rosbridge_client_cpp/rosbridge.h"
#include <memory>

using namespace ftxui;

class BatteryPlugin : public ECTSPlugin {
public:
  BatteryPlugin(std::string name,
                std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
  void sendMessage();
  Component displayData();
  void subscribeToROS();
  std::string getName();
  void unsubscribeFromROS();
  /// update the ftxui visualisation of all battery data for the update
  void calculate();
  std::shared_ptr<std::string> getImportantValues();
  bool isLoaded();

private:
  int maxwidth = 5;
  std::string truncate(std::string str);
  std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
  std::string name;
  float battery_percentage{};
  bool is_critical{};
  int estimated_time{};
  std::string allcontent{};
  std::shared_ptr<std::string> important{};
  std::vector<Element> batteryperel{};
  std::vector<Element> usageel{};
  std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
  rosbridge_client_cpp::Subscriber *batterypersub;
  rosbridge_client_cpp::Subscriber *criticalsub;
  rosbridge_client_cpp::Subscriber *batteryusagesub;
  rosbridge_client_cpp::Subscriber *estTimesub;
  bool loaded = false;
};

#endif // BATTERY_PLUGIN_H