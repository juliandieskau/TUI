#include "ControlPlugin.hpp"

using namespace ftxui;

ControlPlugin::ControlPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  this->name = name;
  ros = rb;
  cmdPub = std::make_shared<rosbridge_client_cpp::Publisher>(*ros, "/ects/control/cmd", "geometry_msgs/Twist.msg", 20);
  
}

/**
 * Serializes linear, angular to JSON and publishes on cmdPub to RosbridgeClient rb
*/
void ControlPlugin::sendMessage(){
  // serialize Vector3 linear to JSON
  picojson::object linJSON;
  linJSON["x"] = picojson::value(linear.x);
  linJSON["y"] = picojson::value(linear.y);
  linJSON["z"] = picojson::value(linear.z);
  // serialize Vector3 angular to JSON
  picojson::object angJSON;
  angJSON["x"] = picojson::value(angular.x);
  angJSON["y"] = picojson::value(angular.y);
  angJSON["z"] = picojson::value(angular.z);
  // append linear ang angular JSON objects to Twist Message
  picojson::object twistJSON;
  twistJSON["linear"] = picojson::value(linJSON);
  twistJSON["angular"] = picojson::value(angJSON);
  cmdPub->publish<picojson::object>(twistJSON);
};

/**
 * Serializes ftxui buttons press state to Twist.msg format 
 * Stores them inside linear, angular
 * TODO
*/
Component ControlPlugin::displayData() {
  std::string name = this->name;
  auto btn_up = Button("up", [&]() { linear.x = 1 });
  auto btn_down = Button("down", [&]() { linear.x = -1 });
  auto btn_right = Button("right", [&]() { linear.y = -1 });
  auto btn_left = Button("left", [&]() { linear.y = 1 });
  auto btn_tright = Button("turn right", [&]() { angular.z = -1 });
  auto btn_tleft = Button("turn left", [&]() { angular.z = 1 });

  auto layout = Container::Horizontal({btn_down, btn_right, btn_up, btn_left, btn_tright, btn_tleft});

  return Renderer(layout, [&] {
    auto element = vbox({vbox({btn_tleft->Render(), btn_up->Render() | vcenter,
                              btn_tright->Render()}),
                        vbox({btn_left->Render(), btn_down->Render() | vcenter,
                              btn_right->Render()})});
    element = element | borderEmpty | border | size(WIDTH, LESS_THAN, 80) |
              size(HEIGHT, LESS_THAN, 20) | center;
    return element;
  });

  sendMessage()
  // reset pressed values
  linear.zero();
  angular.zero();
};

// do nothing, since control only send
void ControlPlugin::subcribeToROS(){
  /* SUBSCRIBERS
   * Topic name "/ects/control/position"
   * Message type "nav_msgs/Odometry.msg" 
   * "Die Position und Ausrich-tung mit Fehler"
   */
};

// do nothing, since control only send
void ControlPlugin::unsubscribeFromRos(){
  // destruktor aufrufen von ALLEN Subscribern, nicht den callbacks!
};

