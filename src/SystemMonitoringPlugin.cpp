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
  auto my_callback2 = [&](const picojson::object& json){ 
    std::string all = "Total usage: " + json["total_usage"].to_str() + " ";
    all = all + "Per core usage: " + json["per_core_usage"].to_str() + "\n";
    all = all + "Per core usage: " + json["load_averages"].to_str();
    cpuUsage = all; };
  rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/system/cpu/usage", "CpuUsage.msg ", my_callback2, 5);
  
  auto my_callback3 = [&](const picojson::object& json){ allcpuUsage = "Usage: " + json["usage"].to_str(); };
  rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/system/cpu/percent", "CpuPercentage.msg", my_callback3, 5);
  
  auto my_callback4 = [&](const picojson::object& json){ 
    std::string all = "Used: " + json["used"].to_str() + " ";
    all = all + "Total: " + json["total"].to_str() + "\n";
    all = all + "Free: " + json["free"].to_str() + " ";
    all = all + "Shared: " + json["shared"].to_str() + "\n";
    all = all + "Buffcache: " + json["buff_cache"].to_str() + " ";
    all = all + "Available: " + json["available"].to_str();
    memoryUsage = all; };
  rosbridge_client_cpp::Subscriber my_sub4(*ros, "/ects/system/mem/usage", "MemoryUsage.msg ", my_callback4, 5);
 
  auto my_callback7 = [&](const picojson::object& json){ totalprocess = "Number of processes: " + json["number_of_processes"].to_str(); };
  rosbridge_client_cpp::Subscriber my_sub7(*ros, "/ects/system/processes/total", "ProcessTotal.msg", my_callback7, 5);

  auto my_callback6 = [&](const picojson::object& json){ 
  //all = v[index].to_str();
  std::string all = all + "Total size: " + json["size_total"].to_str();
  all = all + "Used: " + json["used"].to_str();
  disusage = all; };
  auto my_callback5 = [&](const picojson::object& json){ 
    picojson::value mount = json["rosname"];
    for ( int index = 0; index < v.size(); ++index )
    {
      std::string topic = "/ects/system/disk/" + mount[index].to_str() + "/usage"
      rosbridge_client_cpp::Subscriber my_sub6(*ros, topic, "DiskUsage.msg", my_callback6, 5);
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/disk/" + mount[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub13(*ros, topic, "CpuUsageHistory.msg ", my_callback13, 5);

    } 
   
    };
  auto my_callback9 = [&](const picojson::object& json){ 
    std::string all = "Interfacename: " + json["interface_name"].to_str() + " ";
    all = all + "Ip-address: " + json["human_readable_ip_address"].to_str() + "\n";
    all = all + "Default Gateway: " + json["default_gateway"].to_str() + " ";
    all = all + "DNS-address: " + json["dns_addresses"].to_str() + "\n";
    all = all + "Link is up: " + json["link_is_up"].to_str() + " ";
    all = all + "Wlan ssid: " + json["wlan_ssid"].to_str();

    networkinfo = all; };
  auto my_callback10 = [&](const picojson::object& json){ 
    std::string all = "Down speed: " + json["down_speed"].to_str() + " ";
    all = all + "Up speed: " + json["up_speed"].to_str() + "\n";
    all = all + "Wifi signal strength: " + json["wifi_signal_strength"].to_str();
    networkusage = all; };
  auto my_callback8 = [&](const picojson::object& json){ 
    picojson::value adapter = json["adaptername"];
    for ( int index = 0; index < v.size(); ++index )
    {
      std::string topic = "/ects/system/network/" + adapter[index].to_str() + "/info";
      rosbridge_client_cpp::Subscriber my_sub9(*ros, topic, "NetworkInfo.msg", my_callback9, 5);
      std::string topic = "/ects/system/network/" + adapter[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub10(*ros, topic, "NetworkUsage.msg", my_callback10, 5);
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/network/" + adapter[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub16(*ros, topic, "NetworkUsageHistory.msg", my_callback16, 5);

    }
    
    adapterlist = std::to_string(json); };  

  auto my_callback11 = [&](const picojson::object& json){ 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = "Used: " + v[i].get("used").to_str() + " ";
      all = all + "Total: " + v[i].get("total").to_str() + "\n";
      all = all + "Free: " + v[i].get("free").to_str() + " ";
      all = all + "Shared: " + v[i].get("shared").to_str() + "\n";
      all = all + "Buffcache: " + v[i].get("buff_cache").to_str() + " ";
      all = all + "Available: " + v[i].get("available").to_str();
    }
    memoryUsagehist = all; };
  auto my_callback12 = [&](const picojson::object& json){ 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = "Total usage: " + v[i].get("total_usage").to_str() + " ";
      all = all + "Per core usage: " + v[i].get("per_core_usage").to_str() + "\n";
      all = all + "Per core usage: " + v[i].get("load_averages").to_str();
    }
    allcpuUsagehist = all; };
  auto my_callback14 = [&](const picojson::object& json){ 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = all + "Total size: " + v[i].get("size_total").to_str();
      all = all + "Used: " + v[i].get("used").to_str();
    }
    disusagehist = all; };
  auto my_callback15 = [&](const picojson::object& json) { 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = all + "Number of processes: " + v[i].get("number_of_processes").to_str();
    }
    totalprocesshist = all; 
    };
  auto my_callback13 = [&](const picojson::object& json){ 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = "Total usage: " + v[i].get("total_usage").to_str() + " ";
      all = all + "Per core usage: " + v[i].get("per_core_usage").to_str() + "\n";
      all = all + "Per core usage: " + v[i].get("load_averages").to_str();
    }
    allcpuUsagehistmount = all; };
  auto my_callback16 = [&](const picojson::object& json){ 
    std::string all = "Average duration: " + json["averaging_duration"].to_str() + "\n";
    picojson::value v = json["measurements"];
    for (int i = 0; i < v.size(); i++) {
      std::string all = "Down speed: " + v[i].get("down_speed").to_str() + " ";
      all = all + "Up speed: " + v[i].get("up_speed").to_str() + "\n";
      all = all + "Wifi signal strength: " + v[i].get("wifi_signal_strength").to_str();
    }
    networkhist = all; };

  auto my_callback1 = [&](const picojson::object& json){ 
    picojson::Value v = json["available_aggregations"];
    for ( int index = 0; index < v.size(); ++index )
    {
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/mem/usage";
      rosbridge_client_cpp::Subscriber my_sub11(*ros, topic, "MemoryUsageHistory.msg", my_callback11, 5);
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/cpu/usage";
      rosbridge_client_cpp::Subscriber my_sub12(*ros, topic, "CpuUsageHistory.msg ", my_callback12, 5);
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/cpu/usage";
      rosbridge_client_cpp::Subscriber my_sub14(*ros, topic, "DiskUsageHistory.msg", my_callback14, 5);
      std::string topic = "/ects/system/averages/" + v[index].get("ectsname") + "/processes/total";
      rosbridge_client_cpp::Subscriber my_sub15(*ros, topic, "ProcessTotalHistory.msg", my_callback15, 5);
      rosbridge_client_cpp::Subscriber my_sub5(*ros, "/ects/system/disk/mountpoints", "MountpointList.srv", my_callback5, 5);
      rosbridge_client_cpp::Subscriber my_sub8(*ros, "/ects/system/network/adapters", "AdapterList.srv", my_callback8, 5);


    }
    aggregationlist = std::to_string(json); };
  rosbridge_client_cpp::Subscriber my_sub1(*ros, "/ects/system/aggeragations", "AggregationList.srv", my_callback1, 5);            
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