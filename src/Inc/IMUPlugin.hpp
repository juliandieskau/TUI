#ifndef IMU_PLUGIN_H
#define IMU_PLUGIN_H

#include "ECTSPlugin.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "rosbridge_client_cpp/rosbridge.h"
#include <memory>

using namespace ftxui;

class IMUPlugin : public ECTSPlugin {
public:
  IMUPlugin(std::string name,
            std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
  void sendMessage();
  Component displayData();
  void subscribeToROS();
  std::string getName();
  void unsubscribeFromROS();
  void calculate();
  std::shared_ptr<std::string> getImportantValues();
  bool isLoaded();

private:
  std::string truncate(std::string str);
  int maxwidth = 5;
  std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
  std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
  std::string name;
  std::string allcontent;
  std::shared_ptr<std::string> important;
  std::string orientation;
  std::string angular_velocity;
  std::string linear_acceleration;
  std::vector<Element> allel;
  rosbridge_client_cpp::Subscriber *imucurrentsub;
  bool loaded = false;
};

#endif // IMU_PLUGIN_H