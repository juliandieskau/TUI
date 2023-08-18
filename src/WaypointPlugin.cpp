#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important = std::make_shared<std::string>("Waypoint");
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(*rb, "/ects/retransmit", "ects/ForceRetransmit", 20);

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
              hbox(paragraph(allcontent))
          ) | dim |
              size(WIDTH, EQUAL, 50) | size(HEIGHT, EQUAL, 10)) |
      flex;
  });
  return renderbasic;
};

void WaypointPlugin::subscribeToROS() {
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
    picojson::value val = json["waypoints"]; 
    auto waypointlist = val.get<std::vector<picojson::value>>();
    calculate();
  };
  waypointlistsub = new rosbridge_client_cpp::Subscriber(*ros, "/ects/waypoints/waypoint_list", "ects/WaypointList", my_callback1, 5);
  numwaypointsub = new rosbridge_client_cpp::Subscriber(*ros, "/ects/waypoints/number_of_waypoints", "std_msgs/UInt32", my_callback2, 5);
  currentpointsub = new rosbridge_client_cpp::Subscriber(*ros, "/ects/waypoints/current_waypoint", "std_msgs/UInt32", my_callback3, 5);
  sendMessage();
  loaded = true;
};

void WaypointPlugin::calculate() {
  if (!waypointlist.empty()) {
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
    auto valobj = waypointlist[current_index].get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allval;
    for(std::map<std::string, picojson::value>::iterator it = valobj.begin(); it != valobj.end(); ++it) {
    allval.push_back(it->second);
    }
    //TODO: change allcontent from string to a ftxui component and add all lines as hboxes in a vbox
    allcontent = "Name: " + allval[0].to_str() + " ";
    allcontent = allcontent + "Radius: " + allval[2].to_str() + "\n";
    allcontent = allcontent + "Accuracy: " + allval[3].to_str() + "\n";
    allcontent = allcontent + "Distance to next waypoint: " + std::to_string(distance_to_next) + " ";
    allcontent = allcontent + "Distance to last waypoint: " + std::to_string(total_distance) + "\n";
    *(important) = "Distance to last waypoint: " + std::to_string(total_distance);
    allcontent = allcontent + "Amount of waypoints: " + std::to_string(amount_of_waypoints) + " ";
    allcontent = allcontent + "Next waypoint: " + std::to_string(current_index) + " ";
  }
};

// TODO: implement determineDistance(int index)
float WaypointPlugin::determineDistance(int index) {
    auto valobjf = waypointlist[index].get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allvalf;
    for(std::map<std::string, picojson::value>::iterator it = valobjf.begin(); it != valobjf.end(); ++it) {
    allvalf.push_back(it->second);
   }
   auto koordvalf = allvalf[1].get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allkoordf;
    for(std::map<std::string, picojson::value>::iterator it = koordvalf.begin(); it != koordvalf.end(); ++it) {
    allkoordf.push_back(it->second);
   }
   auto valobjs = waypointlist[index - 1].get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allvals;
    for(std::map<std::string, picojson::value>::iterator it = valobjs.begin(); it != valobjs.end(); ++it) {
    allvals.push_back(it->second);
   }
   auto koordvals = allvals[1].get<std::map<std::string, picojson::value>>();  
    std::vector<picojson::value> allkoords;
    for(std::map<std::string, picojson::value>::iterator it = koordvals.begin(); it != koordvals.end(); ++it) {
    allkoords.push_back(it->second);
   }
  float x = std::stof(allkoordf[0].to_str()) - std::stof(allkoords[0].to_str());
  float y = std::stof(allkoordf[1].to_str()) - std::stof(allkoords[1].to_str());
  float potx = x*x;
  float poty = y*y;
  return sqrt(potx + poty);
};

std::string WaypointPlugin::getName(){
  return name;
};

void WaypointPlugin::unsubscribeFromROS(){
  delete waypointlistsub;
  delete numwaypointsub;
  delete currentpointsub;
  loaded = false;
};

bool WaypointPlugin::isLoaded() {
  return loaded;
}

std::shared_ptr<std::string> WaypointPlugin::getImportantValues() {
  return important;
};