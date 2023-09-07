#include "BatteryPlugin.hpp"
#include "ControlPlugin.hpp"
#include "ECTSPlugin.hpp"
#include "IMUPlugin.hpp"
#include "SystemMonitoringPlugin.hpp"
#include "WaypointPlugin.hpp"
#include "ectsTUI.hpp"
#include <chrono>
#include <thread>

#include "rosbridge_client_cpp/rosbridge.h"

int main(int argc, char *argv[]) {
  // initialize a ROS client
  auto on_connection = []() {}; // TODO: output in ftxui window for messages
  //{ std::cout << "RosbridgeClient connected" << std::endl; };
  auto on_disconnection = []() {}; // TODO: output in ftxui window for messages
  //{ std::cout << "RosbridgeClient disconnected" << std::endl; };

  // check if command line arguments match needed amount
  // if no arguments provided use default values with localhost
  std::string ip("localhost");
  int port = 9090;

  if (argc > 1) {
    ip = argv[1];
  }
  if (argc > 2) {
    port = std::atoi(argv[2]);
  }
  auto rb = std::make_shared<rosbridge_client_cpp::RosbridgeClient>(
      ip, port, on_connection, on_disconnection);

  // initialize the TUI and add the ROS client to it
  ectsTUI tui(rb);

  // initialize an Object for every Plugin
  std::vector<std::shared_ptr<ECTSPlugin>> plugins;
  plugins.push_back(
      std::make_shared<SystemMontitoringPlugin>("System Monitor", rb));
  plugins.push_back(std::make_shared<BatteryPlugin>("Battery", rb));
  plugins.push_back(std::make_shared<IMUPlugin>("Inertia", rb));
  plugins.push_back(std::make_shared<WaypointPlugin>("Waypoints", rb));
  plugins.push_back(std::make_shared<ControlPlugin>("Control", rb));

  // add Plugins to the tui
  for (auto plugin : plugins) {
    tui.addPlugin(plugin);
  }

  // loop over Plugins to display them (loop inside this call)
  // std::thread thr(std::bind(&ectsTUI::setPluginState, tui));
  auto thr = std::thread([&] {
    for (;;) {
      {
        std::lock_guard g{global_mutex};
        tui.setPluginState();
      }
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  // thr.detach();
  tui.main();
  thr.join();

  /*while (true) {
    // loop to hold TUI running even if nothing happens - not sure if needed
  }*/
  return 0;
}
