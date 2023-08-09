# ECTS TUI
[TOC]

## Used Libraries

### ftxui-starter
CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

### rosbridge
[Rosbridge Client](https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/) as ros-bridge library. <br>
Fixed forked version in [GitLab](https://git.scc.kit.edu/pse-robot-monitoring/rosbridge_client_cpp.git)

## Setup project

### VSCode Dev Container:
install [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension <br>
press F1 ">Dev Containers: Open Folder in Container" <br>
and select root folder (that contains .devcontainer)

### Dev Environment (alternatively)
start Docker Desktop / Docker Engine service <br>
open tui project directory in Visual Studio Code <br>
accept pop-up from VSC to run project in Dev Container: C++

## Build instructions
```bash
mkdir build
cd build
cmake -S ../ -B .
make
```

## Test run project (Ubuntu 20.04)
### setup
Update cmake to the newest version. <br>
Install [ROS Noetic](http://wiki.ros.org/noetic/Installation/Ubuntu) <br>
```bash
apt-get update && apt-get install -y ros-noetic-desktop-full ros-noetic-rosbridge-server ros-noetic-catkin gdb iproute2 wireless-tools neovim 
```

### terminal preparation
For every terminal opened for the Backend, run in directory Backend/
```bash
source /devel/setup.bash
source /devel/local_setup.bash
```

### launch backend
Follow launch instructions of the ECTS Backend [README.md](https://git.scc.kit.edu/pse-robot-monitoring/pse/-/blob/main/README.md) to launch `roscore`, `rosbridge` and `ects` in prepared terminals. <br>
Prepare another terminal to call ros service.

### launch ECTS-TUI
from TUI directory
```bash
cd build
./ects-tui
```

# TODO
use VSCode Plugin [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree) for listing them inside the code
## TODO now
- [ ] UNIT TESTS
- [ ] Error Handling
  - [ ] every new also needs a delete, else memory leaks might happen!

## TODO testing phase
- [ ] Code Style/ descriptive Names
- [ ] Documentation for Methods, Classes, Members (-> Entwurf)

# Changes to Draft Phase
- [x] Removed Topic Monitor Plugin (no need for it)
- [x] remove update() methods, not needed (ftxui does it)
- [x] removePlugin() umbenannt zu setPluginState(), subscribed unsubscribed wenn reload button gedrückt, da checkboxes kein onclick event haben und subscribe/unsubscribe nur einmal gecalled werden soll