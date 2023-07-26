cmake_minimum_required (VERSION 3.18.4)


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
FetchContent_Declare(rosbridge_client_cpp
  #GIT_REPOSITORY https://github.com/ppianpak/rosbridgecpp -- was a mistake, wrong repository
  GIT_REPOSITORY https://github.com/antoniocoratelli/rosbridge_client_cpp
  GIT_TAG v2018
)

FetchContent_GetProperties(rosbridge_client_cpp)
if(NOT rosbridge_client_cpp_POPULATED)
  FetchContent_Populate(rosbridge_client_cpp)
  add_subdirectory(${rosbridge_client_cpp_SOURCE_DIR} ${rosbridge_client_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# ------------------------------------------------------------------------------

project(ects-tui
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(ects-tui "src/ectsTUI.cpp")
target_include_directories(ects-tui PRIVATE src)

include_directories(${rosbridge_client_cpp_SOURCE_DIR})
add_subdirectory(${rosbridge_client_cpp_SOURCE_DIR} rosbridge_client_cpp)

target_link_libraries(ects-tui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
  PRIVATE rosbridge_client_cpp::publisher
  PRIVATE rosbridge_client_cpp::subscriber
  PRIVATE rosbridge_client_cpp::rosbridgeclient
)


if (EMSCRIPTEN) 
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 
endif() 
