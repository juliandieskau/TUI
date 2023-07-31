#include "ectsTUI.hpp"
#include "ECTSPlugin.hpp"

ectsTUI::ectsTUI(rosbridge_client_cpp::RosbridgeClient rb) {
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
      auto rend = Renderer([&] {
        return allPlugins[i]->displayData();
      });
      cont->Add(rend | Maybe(&states[i]));
    }
    i++;
  }
  i = 0;
  auto foot = status.displayData();
  Component remnant = Renderer(foot,[&] {
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

  /* while (i < allPlugins.size()) {
    if (*(allPlugins[i]->getshown())) {
      container.push_back(allPlugins[i]->displayDataComp());
    }
    i++;
  }
  i = 0;
  auto cont = Container::Vertical(container);
  auto render = Renderer(cont, [&] {
    return window(text("TUI"), vbox([&] {
                    while (i < container.size()) {
                      container[i]->Render();
                      i++;
                    }
                  }));
  });*/
  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(all);
  return 0;
};
RosbridgeClient* ectsTUI::getRosbridge() {
  return &ros;
};
void ectsTUI::removePlugin(){};
void ectsTUI::addPlugin(ECTSPlugin* plugin) {
  allPlugins.push_back(plugin);
  states[counter] = true;
  manager.addCheckbox(Checkbox(plugin->getName(), &states[counter]));
  counter++;
};
