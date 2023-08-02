#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
   ros = rb;
   this->name = name;
   
};
void WaypointPlugin::sendMessage(){};
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

   };
   auto my_callback1 = [&](const picojson::object& json){
     std::value indx = json["data"];
     current_index = std::stoi(indx.to_str());
   };
   auto my_callback1 = [&](const picojson::object& json){
    waypointlist = json["waypoints"]; 
   };
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/waypoint_list", "WaypointList.msg", my_callback1, 5);   
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/number_of_waypoints", "std_msgs/UInt32.msg", my_callback1, 5);
   rosbridge_client_cpp::Subscriber my_sub2(*ros, "/ects/waypoints/current_waypoint", "std_msgs/UInt32.msg", my_callback1, 5);


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