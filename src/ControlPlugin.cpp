#include "ControlPlugin.hpp"
#include <iostream>

using namespace ftxui;

ControlPlugin::ControlPlugin(
    std::string name,
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  cmdPub = std::make_shared<rosbridge_client_cpp::Publisher>(
      *ros, "/ects/control/cmd", "geometry_msgs/Twist", 20);
  linear.zero();
  angular.zero();
}

/**
 * // TODO: set control mode
 * Serializes linear, angular to JSON and publishes on cmdPub to RosbridgeClient
 * rb
 */
void ControlPlugin::sendMessage() {
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
 */
Component ControlPlugin::displayData() {
  std::string name = this->name;
  auto layout = Container::Horizontal({});
  // reset previous values
  linear.zero();
  angular.zero();

  // get button presses and set corresponding Twist values
  // TODO look if encoding works, must be UTF-8!!
  // using unicode hex codes with \u to insert arrows
  auto btn_up = Button("\u2191", [&] {
    linear.x = 1;
    sendMessage();
  });
  auto btn_down = Button("\u2193", [&] {
    linear.x = -1;
    sendMessage();
  });
  auto btn_right = Button("\u2192", [&] {
    linear.y = -1;
    sendMessage();
  });
  auto btn_left = Button("\u2190", [&] {
    linear.y = 1;
    sendMessage();
  });
  auto btn_tright = Button("\u2197", [&] {
    angular.z = -1;
    sendMessage();
  });
  auto btn_tleft = Button("\u2196", [&] {
    angular.z = 1;
    sendMessage();
  });
  // send if no button is pressed
  if (linear.isZero() && linear.isZero()) {
    sendMessage();
  }

  // add buttons to screen
  layout->Add(btn_up);
  layout->Add(btn_down);
  layout->Add(btn_right);
  layout->Add(btn_left);
  layout->Add(btn_tright);
  layout->Add(btn_tleft);

  auto renderer = Renderer(layout, [=] {
    return window(
        text("Control") | hcenter | bold,
        vbox({
            hbox({btn_tleft->Render(), btn_up->Render(), btn_tright->Render()}),
            hbox({btn_left->Render(), btn_down->Render(), btn_right->Render()})
            // layout->Render()
        }) | size(WIDTH, EQUAL, 9) |
            size(HEIGHT, EQUAL, 9));
  });

  /*{vbox({btn_tleft->Render(), btn_up->Render() | vcenter,
                              btn_tright->Render()}),
                        vbox({btn_left->Render(), btn_down->Render() | vcenter,
                              btn_right->Render()})}) | borderEmpty | border |
     size(WIDTH, LESS_THAN, 80) | size(HEIGHT, LESS_THAN, 20*/
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
void ControlPlugin::unsubscribeFromROS(){
    // destruktor aufrufen von ALLEN Subscribern, nicht den callbacks!
};

std::string ControlPlugin::getName() { return name; };

bool ControlPlugin::isLoaded() { return true; }

std::shared_ptr<std::string> ControlPlugin::getImportantValues() {
  return std::make_shared<std::string>();
}
