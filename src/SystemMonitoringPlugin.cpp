#include "SystemMonitoringPlugin.hpp"

SystemMontitoringPlugin::SystemMontitoringPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  this->name = name;
  ros = rb;
}
void SystemMontitoringPlugin::sendMessage(){};
Component SystemMontitoringPlugin::displayDataComp() {
  return NULL;
};
Element SystemMontitoringPlugin::displayData() {
  std::string name = this->name;
  return window(
             text("System") | hcenter | bold,
             vbox({
                 hbox({text("CPU-Usage:"), filler(), text(cpuUsage + "%")}),
                 hbox({text("All-CPU-Usage:"), filler(),
                       text(allcpuUsage + "%")}),
                 hbox({text("Memory-Usage:"), filler(),
                       text(allcpuUsage + "%")}),
                 hbox(
                     {text("Mountpointlist:"), filler(), text(mountpointlist)}),
                 hbox({text("Disk-Usage:"), filler(), text(disusage + "%")}),
                 hbox({text("Total-Processes:"), filler(), text(totalprocess)}),
                 hbox({text("Adapterlist:"), filler(), text(adapterlist)}),
                 hbox({text("CPU-Usage-History:"), filler(),
                       text(allcpuUsagehist)}),
                 hbox({text("Memory-Usage-History:"), filler(),
                       text(memoryUsagehist)}),
             }) | dim |
                 size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10)) |
         flex;
};
void SystemMontitoringPlugin::subcribeToROS(){ 
  auto my_callback1 = [&](const picojson::object& json){ aggregationlist = std::to_string(json); };
  Subscriber my_sub1(*ros, "/ects/system/aggeragations", "AggregationList.srv", my_callback1, 5);
  
  auto my_callback2 = [&](const picojson::object& json){ cpuUsage = std::to_string(json); };
  Subscriber my_sub2(*ros, "/ects/system/cpu/usage", "CpuUsage.msg ", my_callback2, 5);
  
  auto my_callback3 = [&](const picojson::object& json){ allcpuUsage = std::to_string(json); };
  Subscriber my_sub3(*ros, "/ects/system/cpu/percent", "CpuPercentage.msg", my_callback3, 5);
  
  auto my_callback4 = [&](const picojson::object& json){ memoryUsage = std::to_string(json); };
  Subscriber my_sub4(*ros, "/ects/system/mem/usage", "MemoryUsage.msg ", my_callback4, 5);
  
  auto my_callback5 = [&](const picojson::object& json){ mountpointlist = std::to_string(json); };
  Subscriber my_sub5(*ros, "/ects/system/disk/mountpoints", "MountpointList.srv", my_callback5, 5);
 
  auto my_callback6 = [&](const picojson::object& json){ disusage = std::to_string(json); };
  Subscriber my_sub6(*ros, "/ects/system/disk/{mountpoint}/usage", "DiskUsage.msg", my_callback6, 5);
 
  auto my_callback7 = [&](const picojson::object& json){ totalprocess = std::to_string(json); };
  Subscriber my_sub7(*ros, "/ects/system/processes/total", "ProcessTotal.msg", my_callback7, 5);
  
  auto my_callback8 = [&](const picojson::object& json){ adapterlist = std::to_string(json); };
  Subscriber my_sub8(*ros, "/ects/system/network/adapters", "AdapterList.srv", my_callback8, 5);
  
  auto my_callback9 = [&](const picojson::object& json){ networkinfo= std::to_string(json); };
  Subscriber my_sub9(*ros, "/ects/system/network/{adapter}/info", "NetworkInfo.msg", my_callback9, 5);
  
  auto my_callback10 = [&](const picojson::object& json){ networkusage = std::to_string(json); };
  Subscriber my_sub10(*ros, "/ects/system/network/{adapter}/usage", "NetworkUsage.msg", my_callback10, 5);
  
  auto my_callback11 = [&](const picojson::object& json){ memoryUsagehist = std::to_string(json); };
  Subscriber my_sub11(*ros, "/ects/system/averages/{aggregation_name}/mem/usage", "MemoryUsageHistory.msg", my_callback11, 5);
  
  auto my_callback12 = [&](const picojson::object& json){ allcpuUsagehist = std::to_string(json); };
  Subscriber my_sub12(*ros, "/ects/system/averages/{aggregation_name}/cpu/usage", "CpuUsageHistory.msg ", my_callback12, 5);
  
  auto my_callback13 = [&](const picojson::object& json){ allcpuUsagehist = std::to_string(json); };
  Subscriber my_sub12(*ros, "/ects/system/averages/{aggregation_name}/disk/{mountpoint}/usage", "CpuUsageHistory.msg ", my_callback13, 5);
  
  auto my_callback14 = [&](const picojson::object& json){ disusagehist = std::to_string(json); };
  Subscriber my_sub12(*ros, "/ects/system/averages/{aggregation_name}/cpu/usage", "DiskUsageHistory.msg", my_callback14, 5);
  
  auto my_callback15 = [&](const picojson::object& json){ totalprocesshist = std::to_string(json); };
  Subscriber my_sub12(*ros, "/ects/system/averages/{aggregation_name}/processes/total", "ProcessTotalHistory.msg", my_callback15, 5);
  
  auto my_callback16 = [&](const picojson::object& json){ networkhist = std::to_string(json); };
  Subscriber my_sub12(*ros, "/ects/system/averages/{aggregation_name}/network/{adapter}/usage", "NetworkUsageHistory.msg", my_callback16, 5);
};

std::string SystemMontitoringPlugin::getName() {
  return name;
};

void SystemMontitoringPlugin::unsubscribeFromRos(){};
void SystemMontitoringPlugin::update(){};
bool* SystemMontitoringPlugin::getshown() {
  return &(this->shown);
}

std::string SystemMontitoringPlugin::getboolean() {
  return shown ? "true" : "false";
}