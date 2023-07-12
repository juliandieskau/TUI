// Header for all Plugins for the ECTS-TUI

// include guard
#ifndef ECTS_PLUGIN_H
#define ECTS_PLUGIN_H

using namespace ftxui;

// abstract class by containing at least one pure virtual function
// not possible to instantiate so no constructor nor implementation in a cpp file needed.
class ECTSPlugin {
	public:
		// sendMessage(Topic: topic, Message: message)
		virtual void sendMessage(int topic, int message) = 0;
		// displayData(): Component
		virtual Component displayData() = 0;
		// subcribeToROS(rbClient: RosbridgeClient)
		virtual void subcribeToROS(int RosbridgeClient) = 0;
		// getName(): string
		virtual std::string getName() = 0;
		// unsubscribeFromRos(rbClient: RosbridgeClient)
		virtual void unsubscribeFromRos(int RosbridgeClient) = 0;
		// update()
		virtual void update() = 0;
};

// Plugin that monitors system data and outputs them
class SystemMonitorPlugin : public ECTSPlugin {

};

// Plugin that is used to control the robot manually
class ControlPlugin : public ECTSPlugin {

};

// Plugin that is used to control the robot by Waypoints and manage the latter
class WaypointPlugin : public ECTSPlugin {

};

// Plugin that monitors metadata of ROS-Topics 
class TopicMonitorPlugin : public ECTSPlugin {

};

// Plugin that is used to monitor the battery charge of the robot
class BatteryPlugin : public ECTSPlugin {

};

// Plugin that is used to output IMU data
class IMUPlugin : public ECTSPlugin {

};

#endif ECTS_PLUGIN_H