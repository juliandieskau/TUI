#include "WaypointPlugin.hpp"

WaypointPlugin::WaypointPlugin(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
   ros = rb; 
}