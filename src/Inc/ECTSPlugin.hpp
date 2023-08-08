#ifndef ECTS_PLUGIN_H
#define ECTS_PLUGIN_H

#include <memory>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

// abstract class by containing at least one pure virtual function
// not possible to instantiate so no constructor nor implementation in a cpp file needed.
/**
 * Interface für alle Frontend-Plugins. Deklariert, welche Methoden Plugins realisieren müs-sen, 
 * um im TUI angezeigt werden zu können. 
 * 
 * Erbende Klassen müssen im Konstruktor einen RosbridgeClient übergeben bekommen, auf den methoden dann zugreifen können!
 */
class ECTSPlugin {
  public:
    ECTSPlugin() {};
    /// Sendet als Publisher eine Nachricht auf den jeweiligen Topic.
    virtual void sendMessage() = 0;
    /// Gibt FTXUI-Komponente zurück, die die Daten des Plugins darstellt um dann ins TUI eingefügt zu werdem.
    virtual Component displayData() = 0;
    /// Subscribed auf - vom Plugin benötigte - ROS-Topics in überreichtem ROS-Client.
    virtual void subcribeToROS() = 0;
    /// Unsubscribed von - vom Plugin benötigten - ROS-Topics in überreichtem ROS-Client.
    virtual void unsubscribeFromRos() = 0;
    /// Gibt den Namen des Plugins als string zurück.
    virtual std::string getName() = 0;
    /// TODO: unused/undefined yet
    virtual std::string getboolean() = 0;
    /// Gibt Werte zurück, die in der Status-Bar angezeigt werden können.
    virtual std::vector<std::shared_ptr<std::string>> getImportantValues() = 0;
  
  private:
};


#endif //ECTS_PLUGIN_H
