#include "IMUPlugin.hpp"

IMUPlugin::IMUPlugin(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
    ros = rb;
}