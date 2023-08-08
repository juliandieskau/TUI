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
class ECTSPlugin {
public:
	ECTSPlugin() {};
	virtual void sendMessage() = 0;
	virtual Component displayData() = 0;
	virtual void subcribeToROS() = 0;
	virtual std::string getName() = 0;
	virtual void unsubscribeFromRos() = 0;
	virtual void update() = 0; //useless function, ftxui does it already so remove at some point
	virtual std::string getboolean() = 0;
	virtual std::vector<std::shared_ptr<std::string>> getImportantValues() = 0;

private:
};


#endif //ECTS_PLUGIN_H
