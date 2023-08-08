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

class ControlPlugin : public ECTSPlugin {
public:
    ControlPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage(int topic, int message);
    Component displayData();
    void subcribeToROS();
    std::string getName() { return name; };
    void unsubscribeFromRos();
    void update();
    std::string getboolean() {
        return shown ? "true" : "false";
    }

private:
    bool up;
    bool down;
    bool left;
    bool right;
    bool* shown;
    std::string name;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
};

#endif //CONTROL_PLUGIN_H