cmake_minimum_required(VERSION 3.5)
project(sine)
include_directories(/usr/local/include)
add_executable(sine sine.c)
target_link_libraries(sine /usr/local/lib/libjack.dylib) 



