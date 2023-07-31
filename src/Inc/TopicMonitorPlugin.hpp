#ifndef TOPIC_MONITOR_PLUGIN_H
#define TOPIC_MONITOR_PLUGIN_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;
class TopicMonitorPlugin {
    private:
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
    public:
    TopicMonitorPlugin(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
};
#endif //TOPIC_MONITOR_PLUGIN_H