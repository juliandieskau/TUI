#ifndef TEMPLATE_PLUGIN_H
#define TEMPLATE_PLUGIN_H

#include "ECTSPlugin.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "rosbridge_client_cpp/rosbridge.h"
#include <memory>

using namespace ftxui;

class TemplatePlugin : public ECTSPlugin {
public:
  TemplatePlugin(std::string name,
            std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb);
  void sendMessage();
  Component displayData();
  void subscribeToROS();
  std::string getName();
  void unsubscribeFromROS();
  std::shared_ptr<std::string> getImportantValues();
  bool isLoaded();

private:
  std::shared_ptr<rosbridge_client_cpp::Publisher> templatePublisher;
  std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> ros;
  std::string name;
  rosbridge_client_cpp::Subscriber *templateSubscriber;
  std::vector<Element> tuiOutput;
  std::shared_ptr<std::string> important;
  bool loaded = false;
};

#endif // TEMPLATE_PLUGIN_H