#include "ControlPlugin.hpp"
#include <iostream>

using namespace ftxui;

ControlPlugin::ControlPlugin(std::string name, std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  std::cout << "control plugin constructor called\n";
  ros = rb;
  this->name = name;
  cmdPub = std::make_shared<rosbridge_client_cpp::Publisher>(*ros, "/ects/control/cmd", "geometry_msgs/Twist", 20);
  //linear = new Vector3();
  //angular = new Vector3();
  std::cout << "control plugin created\n";
}

/**
 * // TODO: set control mode
 * Serializes linear, angular to JSON and publishes on cmdPub to RosbridgeClient rb
*/
void ControlPlugin::sendMessage(){
  // serialize Vector3 linear to JSON
  /*
  picojson::object linJSON;
  linJSON["x"] = picojson::value((*linear).x);
  linJSON["y"] = picojson::value((*linear).y);
  linJSON["z"] = picojson::value((*linear).z);
  // serialize Vector3 angular to JSON
  picojson::object angJSON;
  angJSON["x"] = picojson::value((*angular).x);
  angJSON["y"] = picojson::value((*angular).y);
  angJSON["z"] = picojson::value((*angular).z);
  // append linear ang angular JSON objects to Twist Message
  picojson::object twistJSON;
  twistJSON["linear"] = picojson::value(linJSON);
  twistJSON["angular"] = picojson::value(angJSON);
  cmdPub->publish<picojson::object>(twistJSON);*/
};

/**
 * Serializes ftxui buttons press state to Twist.msg format 
 * Stores them inside linear, angular
*/
Component ControlPlugin::displayData() {
  std::cout << "ControlPlugin::displayData() reached\n";
  std::string name = this->name;
  auto layout = Container::Horizontal({});
  // reset previous values
  /*
  (*linear).zero();
  (*angular).zero();
  std::cout << "ControlPlugin: linear/angular zero() worked\n";
  

  auto btn_up = Button("up", [&] { (*linear).x = 1; sendMessage(); });
  auto btn_down = Button("down", [&] { (*linear).x = -1; sendMessage(); });
  auto btn_right = Button("right", [&] { (*linear).y = -1; sendMessage(); });
  auto btn_left = Button("left", [&] { (*linear).y = 1; sendMessage(); });
  auto btn_tright = Button("turn right", [&] { (*angular).z = -1; sendMessage(); });
  auto btn_tleft = Button("turn left", [&] { (*angular).z = 1; sendMessage(); });
  std::cout << "ControlPlugin btn_* defined\n";

  layout->Add(btn_up);
  layout->Add(btn_down);
  layout->Add(btn_right);
  layout->Add(btn_left);
  layout->Add(btn_tright);
  layout->Add(btn_tleft);
  */
  auto renderer = Renderer(layout, [=] {
    return window(
      text("Control") | hcenter | bold,
      vbox({
        layout->Render()
      }) | dim |
      size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 20))
    | flex;
  });

  /*{vbox({btn_tleft->Render(), btn_up->Render() | vcenter,
                              btn_tright->Render()}),
                        vbox({btn_left->Render(), btn_down->Render() | vcenter,
                              btn_right->Render()})}) | borderEmpty | border | size(WIDTH, LESS_THAN, 80) |
              size(HEIGHT, LESS_THAN, 20*/
  std::cout << "ControlPlugin returns now\n";
  return renderer;
};

// do nothing, since control only send
void ControlPlugin::subscribeToROS(){
  /* SUBSCRIBERS
   * Topic name "/ects/control/position"
   * Message type "nav_msgs/Odometry.msg" 
   * "Die Position und Ausrichtung mit Fehler"
   * (falls man noch position anzeigen will, ob sich was verändert)
   */
};

// do nothing, since control only send
void ControlPlugin::unsubscribeFromRos(){
  // destruktor aufrufen von ALLEN Subscribern, nicht den callbacks!
};

std::string ControlPlugin::getName() {
  return name;
};

bool ControlPlugin::isLoaded() {
  return true;
}

std::shared_ptr<std::string> ControlPlugin::getImportantValues() {
  return std::make_shared<std::string>();
}

