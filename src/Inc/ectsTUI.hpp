#ifndef ECTS_PTUI_H
#define ECTS_PTUI_H
#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ECTSPlugin.hpp"
#include <array>
#include "PluginManager.hpp"
#include "Statusbar.hpp"
#include <iostream>
#include <thread>
#include "rosbridge_client_cpp/rosbridge.h"
using namespace ftxui;
class ectsTUI {
private:
    std::vector<ECTSPlugin*> allPlugins;
    std::array<bool,25> states;
    int counter;
    PluginManager manager;
    Statusbar status;
    rosbridge_client_cpp::RosbridgeClient ros;
public:
    ectsTUI(rosbridge_client_cpp::RosbridgeClient rb);
    int main();
    rosbridge_client_cpp::RosbridgeClient* getRosbridge();
    void removePlugin();
    void addPlugin(ECTSPlugin* plugin);
};
#endif //ECTS_PTUI_H