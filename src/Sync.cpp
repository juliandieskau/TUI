#include "Sync.hpp"

rosbridge_client_cpp::Subscriber *
subscribe(rosbridge_client_cpp::RosbridgeClient &rb, const std::string &topic,
          const std::string &type, rosbridge_client_cpp::TopicCallback callback,
          int queue_size) {
  // NOTE: instead of taking the global lock, this could be done in a more
  // granular fashion
  auto mutex_callback = [callback = std::move(callback),
                         topic = topic](const picojson::object &json) {
    std::lock_guard g(global_mutex);
    callback(json);
  };
  return new rosbridge_client_cpp::Subscriber(rb, topic, type, mutex_callback,
                                              queue_size);
}