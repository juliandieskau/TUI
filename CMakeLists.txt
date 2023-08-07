cmake_minimum_required (VERSION 3.18.4)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# --- Fetch FTXUI --------------------------------------------------------------
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --- Fetch rosbridgecpp
FetchContent_Declare(rosbridge_client
  #GIT_REPOSITORY https://github.com/ppianpak/rosbridgecpp -- was a mistake, wrong repository
  #GIT_REPOSITORY https://github.com/antoniocoratelli/rosbridge_client_cpp
  GIT_REPOSITORY https://git.scc.kit.edu/pse-robot-monitoring/rosbridge_client_cpp.git
  GIT_TAG v2018
)

FetchContent_GetProperties(rosbridge_client)
if(NOT rosbridge_client_POPULATED)
  FetchContent_Populate(rosbridge_client)
  add_subdirectory(${rosbridge_client_SOURCE_DIR} ${rosbridge_client_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# ------------------------------------------------------------------------------
project(ects-tui
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(ects-tui "src/main.cpp" "src/ectsTUI.cpp" "src/PluginManager.cpp" "src/StatusBar.cpp" "src/SystemMonitoringPlugin.cpp" "src/ControlPlugin.cpp" "src/WaypointPlugin.cpp" "src/BatteryPlugin.cpp" "src/IMUPlugin.cpp")
target_include_directories(ects-tui PRIVATE src/Inc)

include_directories(${rosbridge_client_SOURCE_DIR})
#add_subdirectory(${rosbridge_client_SOURCE_DIR} rosbridge_client)
include_directories(src/Inc)
target_include_directories(ects-tui PRIVATE ${rosbridge_client_cpp_SOURCE_DIR}/include)
target_include_directories(ects-tui PRIVATE ${rosbridge_client_cpp_SOURCE_DIR}/include/rosbridge_client_cpp/vendor)

target_link_libraries(ects-tui
PRIVATE ftxui::screen
PRIVATE ftxui::dom
PRIVATE ftxui::component # Not needed for this example.
PRIVATE rosbridge_client_cpp
)

if (EMSCRIPTEN) 
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 
endif() 
