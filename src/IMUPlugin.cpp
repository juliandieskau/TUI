#include "IMUPlugin.hpp"

IMUPlugin::IMUPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important = std::make_shared<std::string>("IMU");
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
}

void IMUPlugin::sendMessage() {
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/imu/current");
  (*my_pub).publish<picojson::object>(json);
};

Component IMUPlugin::displayData() {
  std::string name = this->name;
  
  auto renderbasic = Renderer([&] {
  return window(
            text("IMU") | hcenter | bold,
            vbox(
                hbox(paragraph(allcontent))
            ) | dim |
                size(WIDTH, EQUAL, 50) | size(HEIGHT, EQUAL, 10)) |
        flex;
      }
  );
  return renderbasic;
};

void IMUPlugin::subscribeToROS() { 
  auto my_callback4 = [&](const picojson::object& json1){ 
    picojson::object json = json1; 
    picojson::value val = json["orientation"]; 
    auto valobj = val.get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allval;
    for(std::map<std::string, picojson::value>::iterator it = valobj.begin(); it != valobj.end(); ++it) {
    allval.push_back(it->second);
    }
    
    picojson::value valang = json["angular_velocity"]; 
    auto valobjang = valang.get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allvalang;
    for(std::map<std::string, picojson::value>::iterator it = valobjang.begin(); it != valobjang.end(); ++it) {
    allvalang.push_back(it->second);
    }
    
    picojson::value vallin = json["linear_acceleration"]; 
    auto valobjlin = vallin.get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allvallin;
    for(std::map<std::string, picojson::value>::iterator it = valobjlin.begin(); it != valobjlin.end(); ++it) {
    allvallin.push_back(it->second);
    }
    
    orientation = "[" + allval[0].to_str() + "]" + "[" + allval[1].to_str() + "]" +
    "[" + allval[2].to_str() + "]" + "[" + allval[3].to_str() + "]\n";
    angular_velocity = "[" + allvalang[0].to_str() + "]" + 
    "[" + allvalang[1].to_str() + "]" + "[" + allvalang[2].to_str() + "]\n";
    linear_acceleration = "[" + allvallin[0].to_str() + "]" + 
    "[" + allvallin[1].to_str() + "]" + "[" + allvallin[2].to_str() + "]\n"; 
    calculate();
    };
  imucurrentsub = new rosbridge_client_cpp::Subscriber(*ros, "/etcs/imu/current", "sensor_msgs/Imu", my_callback4, 5);
  sendMessage();
  loaded = true;
};

void IMUPlugin::calculate() {
  allcontent = "Orientation: " + orientation + "\n";
  *(important) = allcontent;
  allcontent = allcontent + "Angular velocity: " + angular_velocity + "\n"; 
  allcontent = allcontent + "Linear acceleration: " + linear_acceleration + "\n";
};

std::string IMUPlugin::getName() {
  return name;
};

void IMUPlugin::unsubscribeFromROS() {
  delete imucurrentsub;
  loaded = false;
};

bool IMUPlugin::isLoaded() {
  return loaded;
}

std::shared_ptr<std::string> IMUPlugin::getImportantValues() {
  return important;
};