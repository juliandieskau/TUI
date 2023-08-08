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

class BatteryPlugin : public ECTSPlugin {
    public:
    BatteryPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    Component displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void calculate();
    std::vector<std::shared_ptr<std::string>> getImportantValues();
    private:
    std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
    std::string name;
    float battery_percentage;
    bool is_critical;
    int estimated_time;
    std::string battery_state;
    std::string allcontent;
    std::vector<std::shared_ptr<std::string>> important;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
};

#endif //BATTERY_PLUGIN_H