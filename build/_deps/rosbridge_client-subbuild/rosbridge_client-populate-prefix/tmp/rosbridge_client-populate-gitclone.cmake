
if(NOT "/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitinfo.txt" IS_NEWER_THAN "/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/workspaces/tui/build/_deps/rosbridge_client-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/workspaces/tui/build/_deps/rosbridge_client-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/local/bin/git"  clone --no-checkout "https://github.com/antoniocoratelli/rosbridge_client_cpp" "rosbridge_client-src"
    WORKING_DIRECTORY "/workspaces/tui/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/antoniocoratelli/rosbridge_client_cpp'")
endif()

execute_process(
  COMMAND "/usr/local/bin/git"  checkout v2018 --
  WORKING_DIRECTORY "/workspaces/tui/build/_deps/rosbridge_client-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2018'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/local/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/workspaces/tui/build/_deps/rosbridge_client-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/workspaces/tui/build/_deps/rosbridge_client-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitinfo.txt"
    "/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/workspaces/tui/build/_deps/rosbridge_client-subbuild/rosbridge_client-populate-prefix/src/rosbridge_client-populate-stamp/rosbridge_client-populate-gitclone-lastrun.txt'")
endif()

