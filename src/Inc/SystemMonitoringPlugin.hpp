#ifndef SYSTEM_MONITORING_PLUGIN_H
#define SYSTEM_MONITORING_PLUGIN_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;

class SystemMontitoringPlugin : public ECTSPlugin {
public:
    SystemMontitoringPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    Component displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void update();
    bool* getshown();
    std::string getboolean();
    void addtabadapter(std::string name, std::string content);
    void addtabmountpoint(std::string name, std::string content);
private:
    bool shown;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    std::string name;
    std::string cpuUsage = "20";
    std::string allcpuUsage = "30";
    std::string memoryUsage = "40";
    std::string totalprocess = "2";
    std::vector<Component> adapters;
    std::vector<Component> mountpoints;
    std::vector<std::string> name_adapters;
    int mountpoint_tab_selected = 0;
    std::vector<std::string> name_mountpoints;
    int adapter_tab_selected = 0;
};


#endif //SYSTEM_MONITORING_PLUGIN_H