#ifndef CONTROL_PLUGIN_H
#define CONTROL_PLUGIN_H

#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;

struct Vector3 {
  double x, y, z;
  Vector3() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
  void zero() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
};

class ControlPlugin : public ECTSPlugin {
  public:
    ControlPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    // ECTSPlugin inherited methods
    void sendMessage();
    Component displayData();
    void subcribeToROS();
    std::string getName() { return name; };
    void unsubscribeFromRos();
    std::vector<std::shared_ptr<std::string>> getImportantValues();
  
  private:
    // control state variables
    Vector3 linear = new Vector3;
    Vector3 angular = new Vector3;
    bool up, down, left, right;
    std::string name;
    // ROS Client variables
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    std::shared_ptr<rosbridge_client_cpp::Publisher> cmdPub;
};

#endif //CONTROL_PLUGIN_H