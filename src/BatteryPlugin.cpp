#include <BatteryPlugin.hpp>

BatteryPlugin::BatteryPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important.push_back(std::make_shared<std::string>("")); 
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
}

void BatteryPlugin::sendMessage() {
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/battery/percentage");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/battery/is_critical");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/battery/usage");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/battery/estimated_time_");
  (*my_pub).publish<picojson::object>(json);
};

Component BatteryPlugin::displayData() {
  std::string name = this->name;
  auto renderbasic = Renderer([&] {
  // Color if Battery is low
  return window(
            text("Battery") | hcenter | bold,
            vbox(
                hbox(text(allcontent))
            ) | dim |
                size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10)) |
        flex;
      }
  );
  return renderbasic;
};

void BatteryPlugin::subscribeToROS() {   
  auto my_callback3 = [&](const picojson::object& json1) { 
    picojson::object json = json1; 
    picojson::value v = json["data"]; 
    battery_percentage = std::stoi(v.to_str()) + 1.0;
    *(important[0]) = "Battery percentage: " + std::to_string(battery_percentage);
    calculate();
  };
  batterypersub = new rosbridge_client_cpp::Subscriber(*ros, "/etcs/battery/percentage", "std_msgs/Float32", my_callback3, 5);

  auto my_callback2 = [&](const picojson::object& json1){ 
    picojson::object json = json1;
    std::string v = json["data"].to_str(); 
    if (v == "true") {
      is_critical = true;
    }
    else {
      is_critical = false;
    }
    calculate();
    };
  criticalsub = new rosbridge_client_cpp::Subscriber(*ros, "/etcs/battery/is_critical", "std_msgs/Bool", my_callback2, 5);

  auto my_callback1 = [&](const picojson::object& json1){
    picojson::object json = json1; 
    std::string all;
    all = "Batterystate: \n";
    all = all + "Voltage: " + json["voltage"].to_str() + " ";
    all = all + "Current: " + json["current"].to_str() + "\n";
    all = all + "Capacity: " + json["capacity"].to_str() + " ";
    all = all + "Design capacity: " + json["design_capacity"].to_str() + "\n";
    all = all + "Percentage: " + json["percentage"].to_str() + " ";
    
    all = all + "Power supply status: " + json["power_supply_status"].to_str() + "\n";
    all = all + "Power supply health: " + json["power_supply_health"].to_str() + " ";
    all = all + "Power supply technology: " + json["power_supply_technology"].to_str() + "\n";
    
    all = all + "Present: " + json["present"].to_str() + " ";
    all = all + "Location: " + json["location"].to_str() + "\n";
    all = all + "Serial number: " + json["serial_number"].to_str() + " ";
    picojson::value cells = json["cell_voltage"];
    auto v = cells.get<std::vector<picojson::value>>();
    for (int i = 0; i < v.size(); i++) {
      all = all + "Cell " + std::to_string(i) + " voltage: " + v[i].to_str() + "\n";
    }
    battery_state = all;
    calculate();
  };
  batteryusagesub = new rosbridge_client_cpp::Subscriber(*ros, "/ects/battery/usage", "sensor_msgs/BatteryState", my_callback1, 5);

  auto my_callback4 = [&](const picojson::object& json1){ 
    picojson::object json = json1; 
    estimated_time = std::stoi(json["data"].to_str()); 
    calculate();
  };
  estTimesub = new rosbridge_client_cpp::Subscriber(*ros, "/ects/battery/estimated_time_", "std_msgs/Float32", my_callback4, 5);
  
  sendMessage();
  loaded = true;
};

std::string BatteryPlugin::getName() {
  return name;
};

void BatteryPlugin::unsubscribeFromRos() {
  delete batterypersub;
  delete criticalsub;
  delete batteryusagesub;
  delete estTimesub;
  loaded = false;
};

void BatteryPlugin::calculate() {
  allcontent = "Battery percentage: " + std::to_string(battery_percentage) + "\n";
  allcontent = allcontent + "Critical state: " + std::to_string(is_critical) + "\n";
  allcontent = allcontent + "Battery percentage: " + std::to_string(battery_percentage) + "\n";
  allcontent = allcontent + "Estimated time: " + std::to_string(estimated_time) + "\n";
  allcontent = allcontent + battery_state;
}

bool BatteryPlugin::isLoaded() {
  return loaded;
}

std::vector<std::shared_ptr<std::string>> BatteryPlugin::getImportantValues() {
  return important;
};