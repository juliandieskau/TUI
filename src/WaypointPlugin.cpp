#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
   ros = rb;
   this->name = name;
   important.push_back(std::make_shared<std::string>(""));
   my_pub(*rb, "/ects/retransmit", "ForceRetransmit.msg", 20);

};
void WaypointPlugin::sendMessage(){
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/waypoint_list");
  my_pub.publish<picojson::object>(json);
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/number_of_waypoints");
  my_pub.publish<picojson::object>(json);
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/waypoints/current_waypoint");
  my_pub.publish<picojson::object>(json);
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
      }
  )
  return renderbasic;
};
void WaypointPlugin::subcribeToROS() {

   auto my_callback1 = [&](const picojson::object& json){
    amount_of_waypoints = json["data"];
    calculate();
   };
   auto my_callback2 = [&](const picojson::object& json){
     picojson::value indx = json["data"];
     current_index = std::stoi(indx.to_str());
     calculate();
   };
   auto my_callback3 = [&](const picojson::object& json){
    waypointlist = json["waypoints"]; 
    calculate();
   };
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/waypoint_list", "WaypointList.msg", my_callback1, 5);   
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/number_of_waypoints", "std_msgs/UInt32.msg", my_callback2, 5);
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/current_waypoint", "std_msgs/UInt32.msg", my_callback3, 5);
   sendMessage();
};
void WaypointPlugin::calculate() {
   if (waypointlist != null) {
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
      allcontent = "Radius: " + (waypointlist[current_index])["radius"] + " ";
      allcontent = allcontent + "Accuracy: " + (waypointlist[current_index])["heading_accuracy"] + "\n";
      allcontent = allcontent + "Distance to next waypoint: " + distance_to_next + " ";
      allcontent = allcontent + "Distance to last waypoint: " + total_distance + "\n";
      *(important[0]) = "Distance to last waypoint: " + total_distance;
      allcontent = allcontent + "Amount of waypoints: " + amount_of_waypoints + " ";
      allcontent = allcontent + "Next waypoint: " + current_index;

   }

};
float WaypointPlugin::determineDistance(int index) {
   float x = (waypointlist[index])[x] - (waypointlist[index - 1])[x];
   float y = (waypointlist[index])[y] - (waypointlist[index - 1])[y];
   float potx = x*x;
   float poty = y*y;
   return sqrt(potx, poty);
};

std::string WaypointPlugin::getName(){
   return name;
};
void WaypointPlugin::unsubscribeFromRos(){};
void WaypointPlugin::update(){};
bool* WaypointPlugin::getshown(){
   return false;
};
std::string WaypointPlugin::getboolean() {
   return "";
};
std::vector<std::shared_ptr<float>> WaypointPlugin::getImportantValues() {
  return important;
};