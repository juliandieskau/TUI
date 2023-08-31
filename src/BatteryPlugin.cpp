#include <BatteryPlugin.hpp>

BatteryPlugin::BatteryPlugin(
    std::string name,
    std::shared_ptr<rosbridge_client_cpp::RosbridgeClient> rb) {
  ros = rb;
  this->name = name;
  important = std::make_shared<std::string>("battery");
  my_pub = std::make_shared<rosbridge_client_cpp::Publisher>(
      *rb, "/ects/retransmit", "ects/ForceRetransmit", 20);
}

void BatteryPlugin::sendMessage() {
  picojson::object json;
  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/battery/percentage");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/etcs/battery/is_critical");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/battery/usage");
  (*my_pub).publish<picojson::object>(json);

  json["reload_all"] = picojson::value(false);
  json["topic"] = picojson::value("/ects/battery/estimated_time_");
  (*my_pub).publish<picojson::object>(json);
};

Component BatteryPlugin::displayData() {
  std::string name = this->name;
  auto renderbasic = Renderer([&] {
    // Color if Battery is low
    return window(text("Battery") | hcenter | bold,
                  vbox(vbox(batteryperel), vbox(usageel)) | dim |
                      size(WIDTH, EQUAL, 50) | size(HEIGHT, EQUAL, 10)) |
           flex;
  });
  return renderbasic;
};

void BatteryPlugin::subscribeToROS() {
  auto my_callback3 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    picojson::value v = json["data"];
    battery_percentage = std::stoi(v.to_str()) + 1.0;
    *(important) = "Battery percentage: " + std::to_string(battery_percentage);
    calculate();
  };
  batterypersub = new rosbridge_client_cpp::Subscriber(
      *ros, "/etcs/battery/percentage", "std_msgs/Float32", my_callback3, 5);

  auto my_callback2 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    std::string v = json["data"].to_str();
    if (v == "true") {
      is_critical = true;
    } else {
      is_critical = false;
    }
    calculate();
  };
  criticalsub = new rosbridge_client_cpp::Subscriber(
      *ros, "/etcs/battery/is_critical", "std_msgs/Bool", my_callback2, 5);

  auto my_callback1 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    usageel.clear();
    std::string all;
    all = "Batterystate: ";
    usageel.push_back(paragraph(all));
    all = "Voltage: " + truncate(json["voltage"].to_str());
    usageel.push_back(paragraph(all));
    all = "Current: " + truncate(json["current"].to_str());
    usageel.push_back(paragraph(all));
    all = "Capacity: " + truncate(json["capacity"].to_str());
    usageel.push_back(paragraph(all));
    all = "Design capacity: " + truncate(json["design_capacity"].to_str());
    usageel.push_back(paragraph(all));
    all = "Percentage: " + truncate(json["percentage"].to_str()) + "%";
    usageel.push_back(paragraph(all));
    (*important) = all;
    all = "Power supply status: " + json["power_supply_status"].to_str();
    usageel.push_back(paragraph(all));
    all = "Power supply health: " + json["power_supply_health"].to_str();
    usageel.push_back(paragraph(all));
    all =
        "Power supply technology: " + json["power_supply_technology"].to_str();
    usageel.push_back(paragraph(all));
    std::string present = "";
    if (!json["present"].is<picojson::null>()) {
      present = json["present"].to_str();
    }
    all = "Present: " + json["present"].to_str();
    usageel.push_back(paragraph(all));
    std::string loc = "s";
    if (!json["location"].is<picojson::null>()) {
      loc = json["location"].to_str();
    }
    all = "Location: " + loc;
    usageel.push_back(paragraph(all));
    std::string serial = "a";
    if (!json["serial_number"].is<picojson::null>()) {
      serial = json["serial_number"].to_str();
    }
    all = "Serial number: " + serial;
    usageel.push_back(paragraph(all));
    picojson::value cells = json["cell_voltage"];
    auto v = cells.get<std::vector<picojson::value>>();
    for (int i = 0; i < v.size(); i++) {
      all =
          "Cell " + std::to_string(i) + " voltage: " + truncate(v[i].to_str());
      usageel.push_back(paragraph(all));
    }
  };
  batteryusagesub = new rosbridge_client_cpp::Subscriber(
      *ros, "/ects/battery/usage", "sensor_msgs/BatteryState", my_callback1, 5);

  auto my_callback4 = [&](const picojson::object &json1) {
    picojson::object json = json1;
    estimated_time = std::stoi(json["data"].to_str());
    calculate();
  };
  estTimesub = new rosbridge_client_cpp::Subscriber(
      *ros, "/ects/battery/estimated_time_", "std_msgs/Float32", my_callback4,
      5);

  sendMessage();
  loaded = true;
};

std::string BatteryPlugin::getName() { return name; };

void BatteryPlugin::unsubscribeFromROS() {
  delete batterypersub;
  delete criticalsub;
  delete batteryusagesub;
  delete estTimesub;
  loaded = false;
};

void BatteryPlugin::calculate() {
  batteryperel.clear();
  allcontent =
      "Battery percentage: " + truncate(std::to_string(battery_percentage));
  batteryperel.push_back(paragraph(allcontent));
  allcontent = "Critical state: " + truncate(std::to_string(is_critical));
  batteryperel.push_back(paragraph(allcontent));
  allcontent = "Estimated time: " + truncate(std::to_string(estimated_time));
  batteryperel.push_back(paragraph(allcontent));
}

bool BatteryPlugin::isLoaded() { return loaded; }

std::shared_ptr<std::string> BatteryPlugin::getImportantValues() {
  return important;
};

std::string BatteryPlugin::truncate(std::string str) {
  if (str.length() > maxwidth) {
    return str.substr(0, maxwidth);
  }
  return str;
};