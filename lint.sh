#!/bin/bash

cd "$(dirname "$0")"

FILES="$(find src/ -name '*.hpp' -or -name '*.cpp')"
clang-format -i --sort-includes $FILES
cpplint --verbose 5 --linelength 120 --filter=-legal/copyright,-build/c++11,-build/namespaces,-runtime/explicit $FILES
