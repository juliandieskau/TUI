#include "TemplatePlugin.hpp"

// constructor for the Plugin
TemplatePlugin::TemplatePlugin(
    std::string name,
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important = std::make_shared<std::string>("Template");
  templatePublisher = std::make_shared<rosbridge_client_cpp::Publisher>(
      *rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
}

// send data to the backend, can be used for controls as well, for receiving plugins as a force retransmit
void TemplatePlugin::sendMessage() {
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/template");
  (*templatePublisher).publish<picojson::object>(json);
};

// return ftxui Component to show as window in the TUI
Component TemplatePlugin::displayData() {
  std::string name = this->name;

  auto renderbasic = Renderer([&] {
    return window(text("Template") | hcenter | bold, vbox(tuiOutput) | dim |
                                                    size(WIDTH, EQUAL, 50) |
                                                    size(HEIGHT, EQUAL, 10)) |
           flex;
  });
  return renderbasic;
};

// fetch information from backend
void TemplatePlugin::subscribeToROS() {
  auto templateCallback = [&](const picojson::object &jsonConst) {
    // clear previous output
    tuiOutput.clear();
    // parse json of message to variables
    picojson::object json = jsonConst;
    std::string text = json["value"].to_str();
    std::string output = "Template output: " + text;
    // add parsed json to output
    tuiOutput.push_back(paragraph(output));
    // add important value to the status bar text
    *(important) = "status: " + text;
  };
  
  // Create Subscriber on a topic with previous callback
  // This topic and message does not exist, use existing ones of the backend.
  templateSubscriber =
      subscribe(*ros, "/ects/template", "templateMessage", templateCallback, 5);
  
  // create as many callbacks and corresponding subscribers as needed and push_back to the tuiOutput variable
  
  // force retransmit to load information
  sendMessage();
  loaded = true;
};

// get name of the plugin
std::string TemplatePlugin::getName() { return name; };

void TemplatePlugin::unsubscribeFromROS() {
  delete templateSubscriber;
  // add deletes for every created Subscriber
  loaded = false;
};

// if Plugin is currently shown or not
bool TemplatePlugin::isLoaded() { return loaded; }

// get string to show in status bar
std::shared_ptr<std::string> TemplatePlugin::getImportantValues() {
  return important;
};
