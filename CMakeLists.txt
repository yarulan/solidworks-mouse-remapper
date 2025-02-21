cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

add_executable (CMakeProject1 WIN32 "main.cpp"  "hook.cpp" "hook.h" "state.cpp" "state.h" "input.h" "input.cpp")