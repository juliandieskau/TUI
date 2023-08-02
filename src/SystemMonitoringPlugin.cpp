#include "SystemMonitoringPlugin.hpp"

SystemMontitoringPlugin::SystemMontitoringPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  this->name = name;
  ros = rb;
}
void SystemMontitoringPlugin::sendMessage(){};
Component SystemMontitoringPlugin::displayDataComp() {
  return NULL;
};
Component SystemMontitoringPlugin::displayData() {
  std::string name = this->name;
  
  auto renderbasic = Renderer([&] {
  return window(
             text("System") | hcenter | bold,
             vbox({
                 hbox(text(cpuUsage)),
                 hbox(text(allcpuUsage)),
                 hbox(text(memoryUsage)),
                 hbox(text(totalprocess))
             }) | dim |
                 size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10)) |
         flex;
      }
  )
  
  auto tab_menu_adapter = Menu(&name_adapters, &adapter_tab_selected);
  auto tab_container_adapter = Container::Tab(
      adapters,
      &adapter_tab_selected);
  auto tab_menu_mountpoint = Menu(&name_mountpoints, &mountpoint_tab_selected);
  auto tab_container_mountpoint = Container::Tab(
      mountpoints,
      &mountpoint_tab_selected);
  auto container = Container::Horizontal({
      renderbasic
      tab_menu_adapter,
      tab_container_adapter,
      tab_menu_mountpoint,
      tab_container_mountpoint
  });
 
  auto renderer = Renderer(container, [&] {
    return hbox({
               renderbasic->Render(),
               seperator(),
               tab_menu_adapter->Render(),
               separator(),
               tab_container_adapter->Render(),
               seperator(),
               tab_menu_mountpoint->Render(),
               separator(),
               tab_container_mountpoint->Render()
           }) |
           border;
  });
};

void SystemMontitoringPlugin::subcribeToROS(){ 
  //CPU usage
  auto my_callback2 = [&](const picojson::object& json){ 
    std::string all = "Total usage: " + json["total_usage"].to_str() + " ";
    picojson::value usage = json["per_core_usage"];
    picojson::value average = json["load_averages"];
    for (int a = 1; a <= usage.size(); a++) {
      all = all + "Per core usage of Core " + a ": " + usage[a].to_str() + "\n"
    }
    for (int a = 1; a <= average.size(); a++) {
      all = all + "Per core average of Core " + a ": " + average[a].to_str() + "\n"
    }
    cpuUsage = all; };
  rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/system/cpu/usage", "CpuUsage.msg ", my_callback2, 5);
  
  //CPU percentage
  auto my_callback3 = [&](const picojson::object& json){ allcpuUsage = "Usage: " + json["usage"].to_str(); };
  rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/system/cpu/percent", "CpuPercentage.msg", my_callback3, 5);
  
  //Memory usage
  auto my_callback4 = [&](const picojson::object& json){ 
    std::string all = "Used: " + json["used"].to_str() + " ";
    all = all + "Total: " + json["total"].to_str() + "\n";
    all = all + "Free: " + json["free"].to_str() + " ";
    all = all + "Shared: " + json["shared"].to_str() + "\n";
    all = all + "Buffcache: " + json["buff_cache"].to_str() + " ";
    all = all + "Available: " + json["available"].to_str();
    memoryUsage = all; };
  rosbridge_client_cpp::Subscriber my_sub4(*ros, "/ects/system/mem/usage", "MemoryUsage.msg ", my_callback4, 5);
 
  //Total processes
  auto my_callback7 = [&](const picojson::object& json){ totalprocess = "Number of processes: " + json["number_of_processes"].to_str(); };
  rosbridge_client_cpp::Subscriber my_sub7(*ros, "/ects/system/processes/total", "ProcessTotal.msg", my_callback7, 5);
  
  //Mountpoint Diskusage
  auto my_callback6 = [&](const picojson::object& json){ 
  std::string all = all + "Total size: " + json["size_total"].to_str();
  all = all + "Used: " + json["used"].to_str();
  addtabmountpoint(mount[index].to_str(), all);
  };

  //All Mountpoints
  auto my_callback5 = [&](const picojson::object& json){ 
    picojson::value mount = json["rosname"];
    for ( int index = 0; index < v.size(); ++index )
    {
      std::string topic = "/ects/system/disk/" + mount[index].to_str() + "/usage"
      rosbridge_client_cpp::Subscriber my_sub6(*ros, topic, "DiskUsage.msg", my_callback6, 5);

    } 
   
  };
  rosbridge_client_cpp::Subscriber my_sub5(*ros, "/ects/system/disk/mountpoints", "MountpointList.srv", my_callback5, 5);
  //Networkinfo
  auto my_callback9 = [&](const picojson::object& json){ 
    std::string all = "Interfacename: " + json["interface_name"].to_str() + " ";
    all = all + "Ip-address: " + json["human_readable_ip_address"].to_str() + "\n";
    all = all + "Default Gateway: " + json["default_gateway"].to_str() + " ";
    all = all + "DNS-address: " + json["dns_addresses"].to_str() + "\n";
    all = all + "Link is up: " + json["link_is_up"].to_str() + " ";
    all = all + "Wlan ssid: " + json["wlan_ssid"].to_str();
    addtabadapter(adapter[index].to_str(), all);
    };

  //Networkusage
  auto my_callback10 = [&](const picojson::object& json){ 
    std::string all = "Down speed: " + json["down_speed"].to_str() + " ";
    all = all + "Up speed: " + json["up_speed"].to_str() + "\n";
    all = all + "Wifi signal strength: " + json["wifi_signal_strength"].to_str();
    addtabadapter(adapter[index].to_str(), all);
    };

  //All Adapters
  auto my_callback8 = [&](const picojson::object& json){ 
    picojson::value adapter = json["adaptername"];
    for ( int index = 0; index < v.size(); ++index )
    {
      std::string topic = "/ects/system/network/" + adapter[index].to_str() + "/info";
      rosbridge_client_cpp::Subscriber my_sub9(*ros, topic, "NetworkInfo.msg", my_callback9, 5);
      std::string topic = "/ects/system/network/" + adapter[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub10(*ros, topic, "NetworkUsage.msg", my_callback10, 5);
    }
    
   };  
   rosbridge_client_cpp::Subscriber my_sub8(*ros, "/ects/system/network/adapters", "AdapterList.srv", my_callback8, 5);
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
void addtabadapter(std::string name, std::string content) {
  auto renderer = Renderer([&] {
    return text(name + "\n" + content);
  });
  adapters.push_back(renderer);
  name_adapters.push_back(name);
}
void addtabmountpoint(std::string name, std::string content) {
  auto renderer = Renderer([&] {
    return text(name + ":\n" + content);
  });
  mountpoints.push_back(renderer);
  name_mountpoints.push_back(name);
}