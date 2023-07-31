#include <PluginManager.hpp>
#include <ECTSPlugin.hpp>

using namespace ftxui;
PluginManager::PluginManager() {
  container = Container::Vertical({});
};

Component PluginManager::displayData(){
  return container;
};

void PluginManager::addCheckbox(Component check){
    container->Add(check);
      
};