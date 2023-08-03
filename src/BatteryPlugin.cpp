#include <BatteryPlugin.hpp>
BatteryPlugin::BatteryPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
}
void BatteryPlugin::sendMessage() {

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
  )
  return renderbasic;
};
void BatteryPlugin::subcribeToROS() {   
 
auto my_callback3 = [&](const picojson::object& json){ 
  std::value v = json["data"]; 
  battery_percentage = std::stoi(v.to_str()) + 1.0;
  };
rosbridge_client_cpp::Subscriber my_sub3(*ros, "/etcs/battery/percentage", "std_msgs/Float32.msg", my_callback3, 5);

auto my_callback2 = [&](const picojson::object& json){ 
  std::string v = json["data"].to_str(); 
  if (v == "true") {
    is_critical = true;
  }
  else {
    is_critical = false;
  }
  
  };
rosbridge_client_cpp::Subscriber my_sub3(*ros, "/etcs/battery/is_critical", "std_msgs/Bool.msg", my_callback2, 5);

auto my_callback1 = [&](const picojson::object& json){ 
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
  std::value v = json["cell_voltage"];
  for (int i = 0; i < v.size(); i++) {
    all = all + "Cell " + i + " voltage: " + v[i].to_str() + "\n";
  }
  battery_state = all;
  
  };
rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/battery/usage", "sensor_msgs/BatteryState.msg", my_callback1, 5);

auto my_callback4 = [&](const picojson::object& json){ estimated_time = std::stoi(json["data"].to_str()); };
rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/battery/estimated_time_", "std_msgs/Float32.msg", my_callback4, 5);

};
std::string BatteryPlugin::getName() {
  return name;
};
void BatteryPlugin::unsubscribeFromRos() {

};
void BatteryPlugin::update() {

};
bool* BatteryPlugin::getshown() {

};
std::string BatteryPlugin::getboolean() {

};
void BatteryPlugin::calculate() {
   allcontent = "Battery percentage: " + battery_percentage + "\n";
  allcontent = allcontent + "Critical state: " + is_critical + "\n";
  allcontent = allcontent + "Battery percentage: " + battery_percentage + "\n";
  allcontent = allcontent + "Estimated time: " + estimated_time + "\n";
  allcontent = allcontent + battery_state;

}