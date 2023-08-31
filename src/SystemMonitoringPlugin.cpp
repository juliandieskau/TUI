#include "SystemMonitoringPlugin.hpp"

SystemMontitoringPlugin::SystemMontitoringPlugin(
    std::string name,
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  this->name = name;
  ros = rb;
  important = std::make_shared<std::string>("system");
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(
      *rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
}

void SystemMontitoringPlugin::sendMessage() {
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
    return window(text("System") | hcenter | bold,
                  vbox({
                      window(text("CPU usage") | bold, vbox(allcorepar)),
                      window(text("memory usage") | bold, vbox(memusage)),
                      window(text("processes") | bold, vbox(totalproc)),
                  }) | dim |
                      size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 30)) |
           flex;
  });

  return renderbasic;
};

void SystemMontitoringPlugin::subscribeToROS() {
  // CPU usage
  auto my_callback2 = [&](const picojson::object &json1) {
    allcorepar.clear();
    picojson::object json = json1;

    // total cpu usage
    std::string totalUsage =
        SystemMontitoringPlugin::truncate(json["total_usage"].to_str());
    std::string all = "Total usage: " + totalUsage;
    allcorepar.push_back(paragraph(all));
    *(important) =
        "CPU usage: " + totalUsage; // here the value is correctly inside

    picojson::value usage1 = json["per_core_usage"];
    auto usage = usage1.get<std::vector<picojson::value>>();
    picojson::value average1 = json["load_averages"];
    auto average = average1.get<std::vector<picojson::value>>();

    // usage per core
    allcorepar.push_back(paragraph("Usage per core") | bold);
    for (int a = 0; a < usage.size(); a++) {
      all = "Core " + std::to_string(a + 1) + ": " +
            SystemMontitoringPlugin::truncate(usage[a].to_str());
      allcorepar.push_back(paragraph(all));
    }

    // average cpu usage
    allcorepar.push_back(paragraph("load average") | bold);
    all = "1 minute: " + SystemMontitoringPlugin::truncate(average[0].to_str());
    allcorepar.push_back(paragraph(all));
    all =
        "5 minutes: " + SystemMontitoringPlugin::truncate(average[1].to_str());
    allcorepar.push_back(paragraph(all));
    all =
        "15 minutes: " + SystemMontitoringPlugin::truncate(average[2].to_str());
    allcorepar.push_back(paragraph(all));
  };
  cpuusagesub = new rosbridge_client_cpp::Subscriber(
      *ros, "/ects/system/cpu/usage", "ects/CpuUsage", my_callback2, 5);

  // Memory usage
  auto my_callback4 = [&](const picojson::object &json1) {
    memusage.clear();
    picojson::object json = json1;
    std::string all = "Used: " + json["used"].to_str();
    memusage.push_back(paragraph(all));
    all = "Total: " + json["total"].to_str();
    memusage.push_back(paragraph(all));
    all = "Free: " + json["free"].to_str();
    memusage.push_back(paragraph(all));
    all = "Shared: " + json["shared"].to_str();
    memusage.push_back(paragraph(all));
    all = "Buffcache: " + json["buff_cache"].to_str();
    memusage.push_back(paragraph(all));
    all = "Available: " + json["available"].to_str();
    memusage.push_back(paragraph(all));
  };
  memusagesub = new rosbridge_client_cpp::Subscriber(
      *ros, "/ects/system/mem/usage", "ects/MemoryUsage", my_callback4, 5);

  // Total processes
  auto my_callback7 = [&](const picojson::object &json1) {
    totalproc.clear();
    picojson::object json = json1;
    std::string all =
        "Number of processes: " + json["number_of_processes"].to_str();
    totalproc.push_back(paragraph(all));
  };
  totalprocsub = new rosbridge_client_cpp::Subscriber(
      *ros, "/ects/system/processes/total", "ects/ProcessTotal", my_callback7,
      5);

  sendMessage();
  loaded = true;
};

std::string SystemMontitoringPlugin::truncate(std::string str) {
  if (str.length() > maxwidth) {
    return str.substr(0, maxwidth);
  }
  return str;
};

std::string SystemMontitoringPlugin::getName() { return name; };

void SystemMontitoringPlugin::unsubscribeFromROS() {
  delete cpuusagesub;
  delete cpupersub;
  delete memusagesub;

  // netusagesub.clear();
  loaded = false;
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

bool SystemMontitoringPlugin::isLoaded() { return loaded; }

std::shared_ptr<std::string> SystemMontitoringPlugin::getImportantValues() {
  return important;
};