cmake_minimum_required (VERSION 3.8)

project ("solidworks-mouse-remapper")

add_executable (solidworks-mouse-remapper WIN32 "main.cpp"  "hook.cpp" "hook.h" "state.cpp" "state.h" "input.h" "input.cpp"  "waiting.cpp" "panning.cpp" "rotating.cpp" "result.h" "result.cpp")
