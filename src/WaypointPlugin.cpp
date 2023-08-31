#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(
    std::string name,
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important = std::make_shared<std::string>("Waypoint");
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(
      *rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
};

void WaypointPlugin::sendMessage() {
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

Component WaypointPlugin::displayData() {
  std::string name = this->name;

  auto renderbasic = Renderer([&] {
    return window(text("Waypoint") | hcenter | bold,
                  vbox(allvaltotal) | dim | size(WIDTH, EQUAL, 300) |
                      size(HEIGHT, EQUAL, 20)) |
           flex;
  });
  return renderbasic;
};

void WaypointPlugin::subscribeToROS() {
  auto my_callback2 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    picojson::value indx = json["data"];
    amount_of_waypoints = std::stoi(indx.to_str());
    calculate();
  };
  auto my_callback3 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    picojson::value indx = json["data"];
    current_index = std::stoi(indx.to_str());
    calculate();
  };
  auto my_callback1 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    picojson::value val = json["waypoints"];
    waypointlist = val.get<std::vector<picojson::value>>();
    calculate();
  };
  waypointlistsub = subscribe(*ros, "/ects/waypoints/waypoint_list",
                              "ects/WaypointList", my_callback1, 5);
  numwaypointsub = subscribe(*ros, "/ects/waypoints/number_of_waypoints",
                             "std_msgs/UInt32", my_callback2, 5);
  currentpointsub = subscribe(*ros, "/ects/waypoints/current_waypoint",
                              "std_msgs/UInt32", my_callback3, 5);
  sendMessage();
  loaded = true;
};

void WaypointPlugin::calculate() {
  if (!waypointlist.empty()) {
    allvaltotal.clear();
    amount_of_waypoints = waypointlist.size();
    distance_to_next = 0;
    total_distance = 0;
    for (int i = current_index + 1; i < amount_of_waypoints; i++) {
      total_distance = total_distance + determineDistance(i);
      if (i == current_index + 1) {
        distance_to_next = distance_to_next + determineDistance(i);
      }
    }
    auto valobj = waypointlist[current_index].get<picojson::object>();
    picojson::value allrad = valobj["radius"];
    picojson::value allaccur = valobj["accuracy"];
    picojson::value allname = valobj["name"];
    // TODO: change allcontent from string to a ftxui component and add all
    // lines as hboxes in a vbox
    std::string allcontent;
    allcontent = "Name: " + allname.to_str();
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Radius: " + truncate(allrad.to_str());
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Accuracy: " + truncate(allaccur.to_str());
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Distance to next waypoint: " +
                 truncate(std::to_string(distance_to_next));
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Distance to last waypoint: " +
                 truncate(std::to_string(total_distance));
    allvaltotal.push_back(paragraph(allcontent));
    *(important) = "Distance to last waypoint: " +
                   truncate(std::to_string(total_distance));
    allcontent = "Amount of waypoints: " + std::to_string(amount_of_waypoints);
    allvaltotal.push_back(paragraph(allcontent));
    allcontent = "Next waypoint: " + std::to_string(current_index);
    allvaltotal.push_back(paragraph(allcontent));
  }
}

std::tuple<double, double> WaypointPlugin::position(int index) {
  auto waypoint = waypointlist[index].get<picojson::object>();
  picojson::object pose = waypoint["pose"].get<picojson::object>();
  float x = pose["x"].get<double>();
  float y = pose["y"].get<double>();
  return {x, y};
}

// TODO: implement determineDistance(int index)
float WaypointPlugin::determineDistance(int index) {
  auto [cx, cy] = position(index);
  auto [px, py] = position(index - 1);
  double diff_x = cx - px;
  double diff_y = cy - py;
  double dist = sqrt(diff_x * diff_x + diff_y * diff_y);

  return dist;
};

std::string WaypointPlugin::getName() { return name; };

void WaypointPlugin::unsubscribeFromROS() {
  delete waypointlistsub;
  delete numwaypointsub;
  delete currentpointsub;
  loaded = false;
};

bool WaypointPlugin::isLoaded() { return loaded; }

std::shared_ptr<std::string> WaypointPlugin::getImportantValues() {
  return important;
};

std::string WaypointPlugin::truncate(std::string str) {
  if (str.length() > maxwidth) {
    return str.substr(0, maxwidth);
  }
  return str;
};