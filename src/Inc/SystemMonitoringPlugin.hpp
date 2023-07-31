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
    SystemMontitoringPlugin(std::string name, rosbridge_client_cpp::RosbridgeClient rb);
    void sendMessage();
    Component displayDataComp();
    Element displayData();
    void subcribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    void update();
    bool* getshown();
    std::string getboolean();
private:
    bool shown;
    rosbridge_client_cpp::RosbridgeClient ros;
    std::string name;
    std::string aggregationlist = "";
    std::string cpuUsage = "20";
    std::string allcpuUsage = "30";
    std::string memoryUsage = "40";
    std::string mountpointlist = "{}";
    std::string disusage = "20";
    std::string totalprocess = "2";
    std::string adapterlist = "{}";
    std::string allcpuUsagehist = "30";
    std::string memoryUsagehist = "40";
    std::string disusagehist = "20";
    std::string totalprocesshist = "2";
    std::string networkinfo = "";
    std::string networkusage = "";
    std::string networkhist = "";
};


#endif //SYSTEM_MONITORING_PLUGIN_H