# Base image for compiling
FROM mcr.microsoft.com/devcontainers/cpp:1-debian-11 AS builder
WORKDIR /app
SHELL [ "/bin/bash", "-c" ]

# Copy source files to compile into the container
COPY src/ ./src

# Compile source files using the CMakeLists copied temporarily from the host system
RUN mkdir build 
RUN --mount=type=bind,source=CMakeLists.txt,target=/app/CMakeLists.txt \ 
  cd build && \
  cmake -S ../ -B . && \
  make

# Base image for running the terminal interface
FROM debian
WORKDIR /app

# Set up IP-Configuration needed for the Rosbridge-Client to communicate with the Backend
ARG TUI_IP=127.0.0.1
ARG TUI_PORT=9090
EXPOSE $TUI_PORT

# Copy compiled files from builder 
COPY --from=builder /app/build .

# Install dependencies
#RUN apt update && apt install -y libcurl4

# and run the TUI
ENTRYPOINT [ "./ects-tui", "$TUI_IP", "$TUI_PORT" ]
