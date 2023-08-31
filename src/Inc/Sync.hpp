#pragma once

#include "rosbridge_client_cpp/rosbridge.h"
#include <mutex>

static std::mutex global_mutex{};

rosbridge_client_cpp::Subscriber *
subscribe(rosbridge_client_cpp::RosbridgeClient &rb, const std::string &topic,
          const std::string &type, rosbridge_client_cpp::TopicCallback callback,
          int queue_size = 5);