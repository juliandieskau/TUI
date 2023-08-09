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
#include <array>

using namespace ftxui;

class SystemMontitoringPlugin : public ECTSPlugin {
public:
    SystemMontitoringPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    void sendMessage();
    Component displayData();
    void subscribeToROS();
    std::string getName();
    void unsubscribeFromRos();
    std::string allcontent;
    void addtabadapterUsage(int index);
    void addtabadapterInfo(int index);
    void addtabmountpoint(int index);
    std::vector<std::shared_ptr<std::string>> getImportantValues();
    bool isLoaded();
    
private:
    std::vector<std::string> mountnamestopic;
    std::vector<std::string> adapternamestopic;
    std::shared_ptr<rosbridge_client_cpp::Publisher> my_pub;
    std::vector<std::shared_ptr<std::string>> important;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    rosbridge_client_cpp::Subscriber* cpuusagesub;
    rosbridge_client_cpp::Subscriber* cpupersub;
    rosbridge_client_cpp::Subscriber* memusagesub;
    rosbridge_client_cpp::Subscriber* mountsub;
    rosbridge_client_cpp::Subscriber* adaptersub;
    rosbridge_client_cpp::Subscriber* totalprocsub;
    std::vector<rosbridge_client_cpp::Subscriber*> diskusagesub;
    std::vector<rosbridge_client_cpp::Subscriber*> netinfosub;
    std::vector<rosbridge_client_cpp::Subscriber*> netusagesub;
    std::string name;
    std::string cpuUsage = "20";
    std::string allcpuUsage = "30";
    std::string memoryUsage = "40";
    std::string totalprocess = "2";
    std::vector<Component> adaptersInfo;
    std::vector<Component> adaptersUsage;
    std::vector<Component> mountpoints;
    std::vector<std::string> adaptersInfocontent;
    std::vector<std::string> adaptersUsagecontent;
    std::vector<std::string> mountpointscontent;
    std::vector<std::string> name_adapters;
    int mountpoint_tab_selected = 0;
    int counterm = 0;
    int countera = 0;
    int counteri = 0;
    int sizea = 0;
    int sizem = 0;
    std::vector<std::string> name_mountpoints;
    int adapter_tab_selected = 0;
    bool loaded = false;
};


#endif //SYSTEM_MONITORING_PLUGIN_H