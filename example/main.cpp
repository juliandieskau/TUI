#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;
class ECTSPlugin {
 public:
  ECTSPlugin(){};
  virtual void sendMessage(int topic, int message) = 0;
  virtual Component displayData() = 0;
  virtual void subcribeToROS(int RosbridgeClient) = 0;
  virtual std::string getName() = 0;
  virtual void unsubscribeFromRos(int RosbridgeClient) = 0;
  virtual void update() = 0;

 private:
};

class ectsTUI {
 private:
  std::vector<ECTSPlugin*> allPlugins;

 public:
  ectsTUI(){};
  int main() {
    auto screen = ScreenInteractive::Fullscreen();
    std::vector<Component> comp;
    int size = 20;
    for (int i = 0; i < allPlugins.size(); i++) {
      comp.push_back(allPlugins[i]->displayData());
    }
    auto container = Container::Vertical(comp);
    auto renderer =
        Renderer(container, [&] { return container->Render() | border; });

    screen.Loop(renderer);
    return 0;
  };
  int getRosbridge(){};
  void removePlugin(){};
  void addPlugin(ECTSPlugin* plugin) { allPlugins.push_back(plugin); };
};

class Plugin : public ECTSPlugin {
 public:
  Plugin(std::string name) { this->name = name; }
  void sendMessage(int topic, int message){};
  Component displayData() {
    std::string name = this->name;
    return Renderer([name] { return text(name) | center; });
  };
  void subcribeToROS(int RosbridgeClient){};
  std::string getName() { return name; };
  void unsubscribeFromRos(int RosbridgeClient){};
  void update(){};

 private:
  std::string name;
};

int main() {
  ectsTUI tui;
  ECTSPlugin* e1 = new Plugin("sddjjj");
  ECTSPlugin* e2 = new Plugin("jjsdsj");
  ECTSPlugin* e3 = new Plugin("jdjd");
  tui.addPlugin(e1);
  tui.addPlugin(e2);
  tui.addPlugin(e3);
  tui.main();
}
