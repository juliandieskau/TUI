#include <BatteryPlugin.hpp>
BatteryPlugin::BatteryPlugin(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
}