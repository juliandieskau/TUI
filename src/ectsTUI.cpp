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
  auto statusCont = Container::Horizontal({});

  int i = 0;
  while (i < allPlugins.size()) {
    if (states[i]) {
      statusCont->Add(allPlugins[i]->displayData() | Maybe(&states[i]));
    }
    i++;
  }
  i = 0;

  // Status Bar
  auto foot = statusbar.displayData();
  Component remnant =
      Renderer(foot, [&] { return window(text("Footer"), foot->Render()); });

  // Plugin Checkboxes
  Component state = manager.displayData();
  auto pluginContainer = Container::Vertical({});
  pluginContainer->Add(state);

  auto renderstate = Renderer(pluginContainer, [&] {
    return window(text("Status"), vbox({state->Render()}));
  });

  auto renderPlugin =
      Renderer(statusCont, [&] { return statusCont->Render(); });

  cont->Add(remnant);
  statusCont->Add(renderstate);
  cont->Add(renderPlugin);
  auto all = Renderer(cont, [&] {
    return window(text("TUI"),
                  vbox({renderPlugin->Render(), remnant->Render()}));
  });

  auto screen = ScreenInteractive::Fullscreen();

  auto d = std::thread([&] {
    for (;;) {
      screen.PostEvent(Event::Custom);
      sleep(1);
    }
  });

  screen.Loop(all);
  d.join();

  return 0;
};

/**
 * überprüft ob Plugin angezeigt werden soll und den state von
 * subscribe/unsubscribe und ruft diese auf
 */
void ectsTUI::setPluginState() {
  // loaded in plugins
  // if schleife die überprüft ob schon geloaded oder nicht, während
  // gleichzeitig state true/false allPlugins[i] gehört zu states[i] ->
  // überprüfen

  for (int i = 0; i < counter; i++) {
    if (states[i]) {                    // checkbox angeclicked
      if (!allPlugins[i]->isLoaded()) { // aber plugin nicht loaded (subscribed)
        allPlugins[i]->subscribeToROS();
      }                                // anderer case soll nichts passieren
    } else {                           // checkbox nicht angeclicked
      if (allPlugins[i]->isLoaded()) { // aber plugin noch subscribed
        allPlugins[i]->unsubscribeFromROS();
      }
    }
  }
  std::this_thread::sleep_for(std::chrono::seconds(2));
};

/**
 * Am anfang sind alle Plugins als angezeigt gesetzt
 * Nur initial aufrufen, subscribe und unsubscribe ist über setPluginState()
 */
void ectsTUI::addPlugin(std::shared_ptr<ECTSPlugin> plugin) {
  allPlugins.push_back(plugin);
  states[counter] = true;
  manager.addCheckbox(Checkbox(plugin->getName(), &states[counter]));
  statusbar.addField(plugin);
  counter++;
};
