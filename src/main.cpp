#include "ECTSPlugin.hpp"
#include "ectsTUI.hpp"

#include "SystemMonitoringPlugin.hpp"
#include "BatteryPlugin.hpp"
#include "ControlPlugin.hpp"
#include "IMUPlugin.hpp"
#include "WaypointPlugin.hpp"

#include "rosbridge_client_cpp/rosbridge.h"

int main() {
  // initialize a ROS client
  auto on_connection = []()
  { std::cout << "RosbridgeClient connected" << std::endl; };
  auto on_disconnection = []()
  { std::cout << "RosbridgeClient disconnected" << std::endl; };

  //rosbridge_client_cpp::RosbridgeClient rb("localhost", 9090, on_connection, on_disconnection);
  // rb ist shared_ptr auf RosbridgeClient, nicht ros client selbst!
  auto rb = std::make_shared<rosbridge_client_cpp::RosbridgeClient>("localhost", 9090, on_connection, on_disconnection);
  
  // initialize the TUI and add the ROS client to it
  ectsTUI tui(rb);

  // initialize an Object for every Plugin
  ECTSPlugin* plugin1 = new SystemMontitoringPlugin("System Monitor", rb);
  ECTSPlugin* plugin2 = new BatteryPlugin("Battery", rb);
  ECTSPlugin* plugin3 = new ControlPlugin("Control", rb);
  ECTSPlugin* plugin4 = new IMUPlugin("Inertia", rb);
  ECTSPlugin* plugin5 = new WaypointPlugin("Waypoints", rb);

  // add Plugins to the tui
  tui.addPlugin(plugin1);
  tui.addPlugin(plugin2);
  tui.addPlugin(plugin3);
  tui.addPlugin(plugin4);
  tui.addPlugin(plugin5);

  // loop over Plugins to display them (loop inside this call)
  tui.main();
  
  /*while (true) {
    // loop to hold TUI running even if nothing happens - not sure if needed
  }*/
  return 0;
}