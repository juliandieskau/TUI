#include <BatteryPlugin.hpp>

BatteryPlugin::BatteryPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important.push_back(std::make_shared<std::string>("")); 
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ForceRetransmit.msg", 20);
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

void BatteryPlugin::subcribeToROS() {   
  auto my_callback3 = [&](const picojson::object& json1) { 
    picojson::object json = json1; 
    picojson::value v = json["data"]; 
    battery_percentage = std::stoi(v.to_str()) + 1.0;
    *(important[0]) = "Battery percentage: " + std::to_string(battery_percentage);
    calculate();
  };
  rosbridge_client_cpp::Subscriber my_sub2(*ros, "/etcs/battery/percentage", "std_msgs/Float32.msg", my_callback3, 5);
  batterypersub = &my_sub2;

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
  rosbridge_client_cpp::Subscriber my_sub3(*ros, "/etcs/battery/is_critical", "std_msgs/Bool.msg", my_callback2, 5);
  criticalsub = &my_sub3;

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
  rosbridge_client_cpp::Subscriber my_sub1(*ros, "/ects/battery/usage", "sensor_msgs/BatteryState.msg", my_callback1, 5);
  batteryusagesub = &my_sub1;

  auto my_callback4 = [&](const picojson::object& json1){ 
    picojson::object json = json1; 
    estimated_time = std::stoi(json["data"].to_str()); 
    calculate();
  };
  rosbridge_client_cpp::Subscriber my_sub4(*ros, "/ects/battery/estimated_time_", "std_msgs/Float32.msg", my_callback4, 5);
  estTimesub = &my_sub4;
  
  sendMessage();
};

std::string BatteryPlugin::getName() {
  return name;
};

void BatteryPlugin::unsubscribeFromRos() {
  delete batterypersub;
  delete criticalsub;
  delete batteryusagesub;
  delete estTimesub;
};

void BatteryPlugin::calculate() {
  allcontent = "Battery percentage: " + std::to_string(battery_percentage) + "\n";
  allcontent = allcontent + "Critical state: " + std::to_string(is_critical) + "\n";
  allcontent = allcontent + "Battery percentage: " + std::to_string(battery_percentage) + "\n";
  allcontent = allcontent + "Estimated time: " + std::to_string(estimated_time) + "\n";
  allcontent = allcontent + battery_state;
}

std::vector<std::shared_ptr<std::string>> BatteryPlugin::getImportantValues() {
  return important;
};