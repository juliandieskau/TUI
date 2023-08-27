#ifndef ECTS_PTUI_H
#define ECTS_PTUI_H
#include <chrono>
#include <thread>
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
#include "Statusbar.hpp"
#include <iostream>
#include <thread>
#include "rosbridge_client_cpp/rosbridge.h"

using namespace ftxui;

/**
 * Steht für die Main-Klasse, die eine Schnittstelle zur Rosbridge bildet. Steuert das Frontend
 * und hält alle Objekt-Instanzen, die im Frontend angezeigt werden sollen.
 */
class ectsTUI {
  private:
    std::vector<std::shared_ptr<ECTSPlugin>> allPlugins;
    std::array<bool, 25> states;
    int counter;
    PluginManager manager;
    Statusbar statusbar;
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;

  public:
    ectsTUI(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
    int main();
    void setPluginState();
    void addPlugin(std::shared_ptr<ECTSPlugin> plugin);
};

#endif //ECTS_PTUI_H