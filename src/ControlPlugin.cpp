#include "ControlPlugin.hpp"
using namespace ftxui;

ControlPlugin::ControlPlugin(std::string name, rosbridge_client_cpp::RosbridgeClient rb) {
  this->name = name;
  ros = rb;
}
void ControlPlugin::sendMessage(int topic, int message){};
Element ControlPlugin::displayData() {
  return NULL;
};
Component ControlPlugin::displayDataComp() {
  std::string name = this->name;
  auto btn_up = Button("up", [&]() { up = true; });
  auto btn_down = Button("down", [&]() { down = true; });
  auto btn_right = Button("right", [&]() { right = true; });
  auto btn_left = Button("left", [&]() { left = true; });

  auto layout = Container::Horizontal({btn_down, btn_right, btn_up, btn_left});

  return Renderer(layout, [&] {
    auto element = vbox({vbox({
                             btn_up->Render() | vcenter,
                         }),
                         vbox({btn_left->Render(), btn_down->Render() | vcenter,
                               btn_right->Render()})});
    element = element | borderEmpty | border | size(WIDTH, LESS_THAN, 80) |
              size(HEIGHT, LESS_THAN, 20) | center;
    return element;
  });
};
bool* ControlPlugin::getshown() {
  return shown;
}
void ControlPlugin::subcribeToROS(int RosbridgeClient){};
void ControlPlugin::unsubscribeFromRos(int RosbridgeClient){};
void ControlPlugin::update(){};




