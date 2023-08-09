#include "SystemMonitoringPlugin.hpp"

SystemMontitoringPlugin::SystemMontitoringPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  this->name = name;
  ros = rb;
  important.push_back(std::make_shared<std::string>(""));
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ForceRetransmit.msg", 20);
  
  
}

void SystemMontitoringPlugin::sendMessage(){
  picojson::object json;
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/cpu/percent");
  (*my_pub).publish<picojson::object>(json);
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/cpu/usage");
  (*my_pub).publish<picojson::object>(json);
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/mem/usage");
  (*my_pub).publish<picojson::object>(json);
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/processes/total");
  (*my_pub).publish<picojson::object>(json);
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/disk/mountpoints");
  (*my_pub).publish<picojson::object>(json);
  
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/system/network/adapters");
  (*my_pub).publish<picojson::object>(json);
  
  for (int i = 0; i < mountnamestopic.size(); i++) {
    json["reload_all"] = picojson::value(false);
    json["topic"] = picojson::value(mountnamestopic[i]);
    (*my_pub).publish<picojson::object>(json);
  }
  for (int i = 0; i < adapternamestopic.size(); i++) {
    json["reload_all"] = picojson::value(false);
    json["topic"] = picojson::value(adapternamestopic[i]);
    (*my_pub).publish<picojson::object>(json);
  }
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
      size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10))
    | flex;
  });
  
  Component tab_menu_adapter = Menu(&name_adapters, &adapter_tab_selected);
  Component tab_container_adapter_Info = Container::Tab(
      adaptersInfo,
      &adapter_tab_selected);
  Component tab_container_adapter_Usage = Container::Tab(
      adaptersUsage,
      &adapter_tab_selected);
  Component tab_menu_mountpoint = Menu(&name_mountpoints, &mountpoint_tab_selected);
  Component tab_container_mountpoint = Container::Tab(
      mountpoints,
      &mountpoint_tab_selected);
  Component container = Container::Horizontal({
      renderbasic,
      tab_menu_adapter,
      tab_container_adapter_Info,
      tab_container_adapter_Usage,
      tab_menu_mountpoint,
      tab_container_mountpoint
  });
  
  Component renderer = Renderer(container, [&] {
    return hbox({
      renderbasic->Render(),
      tab_menu_adapter->Render(),
      tab_container_adapter_Usage->Render(),
      tab_container_adapter_Info->Render(),
      tab_menu_mountpoint->Render(),
      tab_container_mountpoint->Render() 
    }) | border;}
  );
  return renderer;
};

void SystemMontitoringPlugin::subcribeToROS(){ 
  //CPU usage
  auto my_callback2 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    std::string all = "Total usage: " + json["total_usage"].to_str() + " ";
    picojson::value usage1 = json["per_core_usage"];
    auto usage = usage1.get<std::vector<picojson::value>>();
    picojson::value average1 = json["load_averages"];
    auto average = average1.get<std::vector<picojson::value>>();
    
    for (int a = 1; a <= usage.size(); a++) {
      all = all + "Per core usage of Core " + std::to_string(a) + ": " + usage[a].to_str() + "\n";
    }
    for (int a = 1; a <= average.size(); a++) {
      all = all + "Per core average of Core " + std::to_string(a) + ": " + average[a].to_str() + "\n";
    }
    cpuUsage = all; 
    };
  rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/system/cpu/usage", "CpuUsage.msg ", my_callback2, 5);
  cpuusagesub = &my_sub2;
  
  //CPU percentage
  auto my_callback3 = [&](const picojson::object& json1) {
    picojson::object json = json1; 
    allcpuUsage = "CPU usage: " + json["usage"].to_str(); 
    *(important[0]) = allcpuUsage;
    };
  rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/system/cpu/percent", "CpuPercentage.msg", my_callback3, 5);
  cpupersub = &my_sub3;
  
  //Memory usage
  auto my_callback4 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    std::string all = "Used: " + json["used"].to_str() + " ";
    all = all + "Total: " + json["total"].to_str() + "\n";
    all = all + "Free: " + json["free"].to_str() + " ";
    all = all + "Shared: " + json["shared"].to_str() + "\n";
    all = all + "Buffcache: " + json["buff_cache"].to_str() + " ";
    all = all + "Available: " + json["available"].to_str();
    memoryUsage = all; 
    };
  rosbridge_client_cpp::Subscriber my_sub4(*ros, "/ects/system/mem/usage", "MemoryUsage.msg ", my_callback4, 5);
  memusagesub = &my_sub4;
  //Total processes
  auto my_callback7 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    totalprocess = "Number of processes: " + json["number_of_processes"].to_str(); 
    };
  rosbridge_client_cpp::Subscriber my_sub7(*ros, "/ects/system/processes/total", "ProcessTotal.msg", my_callback7, 5);
  totalprocsub = &my_sub7;
  //Mountpoint Diskusage
  auto my_callback6 = [&](const picojson::object& json1){ 
  picojson::object json = json1;
  std::string all = all + "Total size: " + json["size_total"].to_str();
  all = all + "Used: " + json["used"].to_str();
  mountpointscontent[counterm] = all;
  if (counterm <= sizem - 1) {
    counterm = 0;
  }
  else {
    counterm++;
  }
  };
  
  //All Mountpoints
  auto my_callback5 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    picojson::value mount1 = json["rosname"];
    auto mount = mount1.get<std::vector<picojson::value>>();
    sizem = sizeof(mount);
    for ( int index = 0; index < mount.size(); ++index )
    {
      std::string topic = "/ects/system/disk/" + mount[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub6(*ros, topic, "DiskUsage.msg", my_callback6 , 5);
      diskusagesub.push_back(&my_sub6);
      mountnamestopic.push_back(topic);
      name_mountpoints.push_back(mount[index].to_str());
      addtabmountpoint(index);
    } 
  
  };
  rosbridge_client_cpp::Subscriber my_sub5(*ros, "/ects/system/disk/mountpoints", "MountpointList.srv", my_callback5, 5);
  mountsub = &my_sub5;
  //Networkinfo
  auto my_callback9 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    std::string all = "Interfacename: " + json["interface_name"].to_str() + " ";
    all = all + "Ip-address: " + json["human_readable_ip_address"].to_str() + "\n";
    all = all + "Default Gateway: " + json["default_gateway"].to_str() + " ";
    all = all + "DNS-address: " + json["dns_addresses"].to_str() + "\n";
    all = all + "Link is up: " + json["link_is_up"].to_str() + " ";
    all = all + "Wlan ssid: " + json["wlan_ssid"].to_str();
    adaptersInfocontent[countera] = all;
    if (countera <= sizea - 1) {
      countera = 0;
    }
    else {
      countera++;
    }
    };
  
  //Networkusage
  auto my_callback10 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    std::string all = "Down speed: " + json["down_speed"].to_str() + " ";
    all = all + "Up speed: " + json["up_speed"].to_str() + "\n";
    all = all + "Wifi signal strength: " + json["wifi_signal_strength"].to_str();
    adaptersUsagecontent[counteri] = all;
    if (counteri <= sizea - 1) {
      counteri = 0;
    }
    else {
      counteri++;
    }
    };
  
  //All Adapters
  auto my_callback8 = [&](const picojson::object& json1){ 
  
    picojson::object json = json1;
    picojson::value adapter1 = json["adaptername"];
    auto adapter = adapter1.get<std::vector<picojson::value>>();
    sizea = sizeof(adapter);
    for ( int index = 0; index < adapter.size(); ++index )
    {
      std::string topic1 = "/ects/system/network/" + adapter[index].to_str() + "/info";
      rosbridge_client_cpp::Subscriber my_sub9(*ros, topic1, "NetworkInfo.msg", my_callback9, 5);
      netinfosub.push_back(&my_sub9);
      std::string topic2 = "/ects/system/network/" + adapter[index].to_str() + "/usage";
      rosbridge_client_cpp::Subscriber my_sub10(*ros, topic2, "NetworkUsage.msg", my_callback10, 5);
      netusagesub.push_back(&my_sub10);
      adapternamestopic.push_back(topic1);
      adapternamestopic.push_back(topic2);
      name_adapters.push_back(adapter[index].to_str());
      addtabadapterInfo(index);
      addtabadapterUsage(index);
    }
    
  };  
  rosbridge_client_cpp::Subscriber my_sub8(*ros, "/ects/system/network/adapters", "AdapterList.srv", my_callback8, 5);
  adaptersub = &my_sub8;
  sendMessage();
};

std::string SystemMontitoringPlugin::getName() {
  return name;
};

void SystemMontitoringPlugin::unsubscribeFromRos(){
  delete cpuusagesub;
  delete cpupersub;
  delete memusagesub;
  delete mountsub;
  delete adaptersub;
  for (int i = 0; i < diskusagesub.size(); i++) {
    delete diskusagesub[i];
  }
  diskusagesub.clear();
  for (int i = 0; i < netinfosub.size(); i++) {
    delete netinfosub[i];
  }
  netinfosub.clear();
  for (int i = 0; i < netusagesub.size(); i++) {
    delete netusagesub[i];
  }
  netusagesub.clear();

};

void SystemMontitoringPlugin::addtabadapterInfo(int index) {
  auto renderer = Renderer([&] {
    return text(name_adapters[index] + "\n" + adaptersInfocontent[index]);
  });
  adaptersInfo.push_back(renderer);
}

void SystemMontitoringPlugin::addtabadapterUsage(int index) {
  auto renderer = Renderer([&] {
    return text(name_adapters[index] + "\n" + adaptersUsagecontent[index]);
  });
  adaptersUsage.push_back(renderer);
}

void SystemMontitoringPlugin::addtabmountpoint(int index) {
  auto renderer = Renderer([&] {
    return text(name_mountpoints[index] + ":\n" + mountpointscontent[index]);
  });
  mountpoints.push_back(renderer);
}

std::vector<std::shared_ptr<std::string>> SystemMontitoringPlugin::getImportantValues() {
  return important;
};