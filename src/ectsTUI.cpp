#include "ectsTUI.hpp"
#include "ECTSPlugin.hpp"

ectsTUI::ectsTUI(std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  counter = 0;
  ros = rb;
  states = {};
};

int ectsTUI::main() {
  std::vector<Component> container;
  auto cont = Container::Horizontal({});
  int i = 0;
  while (i < allPlugins.size()) {
    if (states[i]) {
      cont->Add(allPlugins[i]->displayData() | Maybe(&states[i]));
    }
    i++;
  }
  i = 0;
  auto foot = statusbar.displayData();
  Component remnant = Renderer(foot, [&] {
    return window(text("Footer"), foot->Render());
  });

  Component state = manager.displayData();
  auto renderstate = Renderer(state, [&] {
    return window(text("Status"), state->Render());
  });
  
  cont->Add(remnant);
  cont->Add(renderstate);
  auto all = Renderer(cont, [&] {
    return window(text("TUI"),
                  cont->Render());
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(all);
  return 0;
};

/*RosbridgeClient* ectsTUI::getRosbridge() {
  return &ros;
};*/

void ectsTUI::removePlugin(){};

void ectsTUI::addPlugin(ECTSPlugin* plugin) {
  allPlugins.push_back(plugin);
  states[counter] = true;
  manager.addCheckbox(Checkbox(plugin->getName(), &states[counter]));
  statusbar.addField(&plugin);
  counter++;
};
