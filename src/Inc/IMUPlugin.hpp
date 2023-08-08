#ifndef IMU_PLUGIN_H
#define IMU_PLUGIN_H

#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;

class IMUPlugin : public ECTSPlugin {
    public:
    IMUPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    Component displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void update();
    std::string getboolean();
    void calculate();
    std::vector<std::shared_ptr<std::string>> getImportantValues();
    private:
    std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    std::string name;
    std::string allcontent;
    std::vector<std::shared_ptr<std::string>> important;
    std::string orientation;
    std::string angular_velocity;
    std::string linear_acceleration;
};

#endif //IMU_PLUGIN_H