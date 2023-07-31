#include <TopicMonitorPlugin.hpp>

TopicMonitorPlugin::TopicMonitorPlugin(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
ros = rb;
}