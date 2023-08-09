#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important.push_back(std::make_shared<std::string>(""));
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ForceRetransmit.msg", 20);

};

void WaypointPlugin::sendMessage(){
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/waypoint_list");
  (*my_pub).publish<picojson::object>(json);
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/number_of_waypoints");
  (*my_pub).publish<picojson::object>(json);
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/current_waypoint");
  (*my_pub).publish<picojson::object>(json);
};

Component WaypointPlugin::displayData(){
  std::string name = this->name;
  
  auto renderbasic = Renderer([&] {
    return window(
          text("Waypoint") | hcenter | bold,
          vbox(
              hbox(text(allcontent))
          ) | dim |
              size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 10)) |
      flex;
  });
  return renderbasic;
};

void WaypointPlugin::subcribeToROS() {
  auto my_callback2 = [&](const picojson::object& json1){
    picojson::object json = json1; 
    picojson::value indx = json["data"];
    amount_of_waypoints = std::stoi(indx.to_str());
    calculate();
  };
  auto my_callback3 = [&](const picojson::object& json1){
    picojson::object json = json1; 
    picojson::value indx = json["data"];
    current_index = std::stoi(indx.to_str());
    calculate();
  };
  auto my_callback1 = [&](const picojson::object& json1){
    picojson::object json = json1; 
    waypointlist = json["waypoints"]; 
    calculate();
  };
  rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/waypoint_list", "WaypointList.msg", my_callback1, 5);   
  waypointlistsub = &my_sub2;
  rosbridge_client_cpp::Subscriber my_sub3(*ros, "/ects/waypoints/number_of_waypoints", "std_msgs/UInt32.msg", my_callback2, 5);
  numwaypointsub = &my_sub3;
  rosbridge_client_cpp::Subscriber my_sub4(*ros, "/ects/waypoints/current_waypoint", "std_msgs/UInt32.msg", my_callback3, 5);
  currentpointsub = &my_sub4;
  sendMessage();
  loaded = true;
};

void WaypointPlugin::calculate() {
  if (!waypointlist.is<picojson::null>()) {
    if (current_index - 1 < 0) {
      distance_to_next = 0;
      for (int i = current_index + 1; i < amount_of_waypoints; i++) {
        total_distance = total_distance + determineDistance(i);
        if (i == 1) {
          distance_to_next = distance_to_next + determineDistance(i);
        }
      }
    }
    else {
      distance_to_next = determineDistance(current_index);
      for (int i = current_index; i < amount_of_waypoints; i++) {
        total_distance = total_distance + determineDistance(i);
      }

    }
    /*allcontent = "Radius: " + (waypointlist[current_index])["radius"].to_str() + " ";
    allcontent = allcontent + "Accuracy: " + (waypointlist[current_index])["heading_accuracy"].to_str() + "\n";
    allcontent = allcontent + "Distance to next waypoint: " + std::to_string(distance_to_next) + " ";
    allcontent = allcontent + "Distance to last waypoint: " + std::to_string(total_distance) + "\n";
    *(important[0]) = "Distance to last waypoint: " + std::to_string(total_distance);
    allcontent = allcontent + "Amount of waypoints: " + std::to_string(amount_of_waypoints) + " ";
    allcontent = allcontent + "Next waypoint: " + std::to_string(current_index);*/
  }
};

// TODO: implement determineDistance(int index)
float WaypointPlugin::determineDistance(int index) {
  /*float x = std::stof((waypointlist[index])[x].to_str()) - std::stof((waypointlist[index - 1])[x].to_str());
  float y = std::stof((waypointlist[index])[y].to_str()) - std::stof((waypointlist[index - 1])[y].to_str());
  float potx = x*x;
  float poty = y*y;
  return sqrt(potx, poty);*/
  return 0.0f;
};

std::string WaypointPlugin::getName(){
  return name;
};

void WaypointPlugin::unsubscribeFromRos(){
  delete waypointlistsub;
  delete numwaypointsub;
  delete currentpointsub;
  loaded = false;
};

bool WaypointPlugin::isLoaded() {
  return loaded;
}

std::vector<std::shared_ptr<std::string>> WaypointPlugin::getImportantValues() {
  return important;
};