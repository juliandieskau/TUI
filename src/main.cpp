#include "ECTSPlugin.hpp"
#include "ectsTUI.hpp"
#include "SystemMonitoringPlugin.hpp"
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

  // initialize Plugins
  ECTSPlugin* e1 = new SystemMontitoringPlugin("sddjjj", rb);
  // ECTSPlugin* e2 = new ControlPlugin("jjsdsj");
  ECTSPlugin* e3 = new SystemMontitoringPlugin("jdjd", rb);
  ECTSPlugin* e4 = new SystemMontitoringPlugin("sddjjj", rb);
  ECTSPlugin* e5 = new SystemMontitoringPlugin("jjsdsj", rb);
  ECTSPlugin* e6 = new SystemMontitoringPlugin("jdjd", rb);

  // add Plugins to the tui
  tui.addPlugin(e1);
  // tui.addPlugin(e2);
  tui.addPlugin(e3);
  tui.addPlugin(e4);
  tui.addPlugin(e5);
  tui.addPlugin(e6);

  // loop over Plugins to display them
  tui.main();
  
  /*while (true) {
    // loop to hold TUI running even if nothing happens - not sure if needed
  }*/
  return 0;
}