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
              vbox(allvaltotal)
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
    allvaltotal.clear();
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
    picojson::value allrad;
    picojson::value allaccur;
    picojson::value allname;
    std::string radtag("radius");
    std::string nametag("name");
    std::string acctag("accuracy");
    for(std::map<std::string, picojson::value>::iterator it = valobj.begin(); it != valobj.end(); ++it) {
    if (it->first == radtag) {
      allrad = it->second;
    }
    if (it->first == acctag) {
      allaccur = it->second;
    }
    if (it->first == nametag) {
      allname = it->second;
    }
    }
    //TODO: change allcontent from string to a ftxui component and add all lines as hboxes in a vbox
    std::string allcontent;
    allcontent = "Name: " + allname.to_str();
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Radius: " + truncate(allrad.to_str());
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Accuracy: " + truncate(allaccur.to_str());
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Distance to next waypoint: " + truncate(std::to_string(distance_to_next));
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Distance to last waypoint: " + truncate(std::to_string(total_distance));
    allvaltotal.push_back(paragraph(allcontent));
    *(important) = "Distance to last waypoint: " + truncate(std::to_string(total_distance));
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Amount of waypoints: " + std::to_string(amount_of_waypoints);
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Next waypoint: " + std::to_string(current_index);
    allvaltotal.push_back(paragraph(allcontent));
  }
};

// TODO: implement determineDistance(int index)
float WaypointPlugin::determineDistance(int index) {
    auto valobjf = waypointlist[index].get<std::map<std::string, picojson::value>>();  
    picojson::value allvalf;
    std::string posestr("pose");
    for(std::map<std::string, picojson::value>::iterator it = valobjf.begin(); it != valobjf.end(); ++it) {
    if (it->first == posestr) {
      allvalf = it->second;
    }
   }
   auto koordvalf = allvalf.get<std::map<std::string, picojson::value>>();  
    picojson::value allkoordx;
    picojson::value allkoordy;
    std::string posestrx("x");
    std::string posestry("y");
    for(std::map<std::string, picojson::value>::iterator it = koordvalf.begin(); it != koordvalf.end(); ++it) {
    if (it->first == posestrx) {
      allkoordx = it->second;
    }
    if (it->first == posestry) {
      allkoordy = it->second;
    }
   }
   picojson::value allvalfs;
   auto valobjfs = waypointlist[index - 1].get<std::map<std::string, picojson::value>>();
   for(std::map<std::string, picojson::value>::iterator it = valobjfs.begin(); it != valobjfs.end(); ++it) {
    if (it->first == posestr) {
      allvalfs = it->second;
    }
   }
   auto koordvalfs = allvalfs.get<std::map<std::string, picojson::value>>();  
    picojson::value allkoordxs;
    picojson::value allkoordys;
    for(std::map<std::string, picojson::value>::iterator it = koordvalfs.begin(); it != koordvalfs.end(); ++it) {
    if (it->first == posestrx) {
      allkoordxs = it->second;
    }
    if (it->first == posestry) {
      allkoordys = it->second;
    }
   }
  float x = std::stof(allkoordx.to_str()) - std::stof(allkoordxs.to_str());
  float y = std::stof(allkoordy.to_str()) - std::stof(allkoordys.to_str());
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

std::string WaypointPlugin::truncate(std::string str)
{
    if (str.length() > maxwidth) {
      return str.substr(0, maxwidth);
    }
    return str;
};