#include "IMUPlugin.hpp"

IMUPlugin::IMUPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
    ros = rb;
    this->name = name;
    important.push_back(std::make_shared<std::string>(""));
    my_pub(*rb, "/ects/retransmit", "ForceRetransmit.msg", 20);
}
void IMUPlugin::sendMessage() {
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/imu/current");
  my_pub.publish<picojson::object>(json);
};
Component IMUPlugin::displayData() {
  std::string name = this->name;
  
  auto renderbasic = Renderer([&] {
  return window(
             text("IMU") | hcenter | bold,
             vbox(
                 hbox(text(allcontent))
             ) | dim |
                 size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10)) |
         flex;
      }
  )
  return renderbasic;
};
void IMUPlugin::subcribeToROS() { 
    auto my_callback4 = [&](const picojson::object& json){ 
        orientation = "[" + (json["orientation"])["x"].to_str() + "]" + "[" + (json["orientation"])["y"].to_str() + "]" +
         "[" + (json["orientation"])["z"].to_str() + "]" + "[" + (json["orientation"])["w"].to_str() + "]\n";
        angular_velocity = "[" + (json["angular_velocity"])["x"].to_str() + "]" + 
        "[" + (json["angular_velocity"])["y"].to_str() + "]" + "[" + (json["angular_velocity"])["z"].to_str() + "]\n";
        linear_acceleration = "[" + (json["linear_acceleration"])["x"].to_str() + "]" + 
        "[" + (json["linear_acceleration"])["y"].to_str() + "]" + "[" + (json["linear_acceleration"])["z"].to_str() + "]\n";  
        calculate();
        };
    rosbridge_client_cpp::Subscriber my_sub3(*ros, "/etcs/imu/current", "sensor_msgs/Imu.msg ", my_callback4, 5);
    sendMessage();
};
void IMUPlugin::calculate() {
    allcontent = "Orientation: " + orientation + "\n";
    *(important[0]) = allcontent;
    allcontent = allcontent + "Angular velocity: " + angular_velocity + "\n"; 
    allcontent = allcontent + "Linear acceleration: " + linear_acceleration + "\n";
};
std::string IMUPlugin::getName() {
    return name;
};
void IMUPlugin::unsubscribeFromRos() {

};
void IMUPlugin::update() {

};
bool* IMUPlugin::getshown() {

};
std::string IMUPlugin::getboolean() {

};
std::vector<std::shared_ptr<float>> IMUPlugin::getImportantValues() {
  return important;
};