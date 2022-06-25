cmake_minimum_required(VERSION 3.22)
project(2_cinemaLib)

set(CMAKE_CXX_STANDARD 14)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_executable(2_cinemaLib main.cpp)

target_link_libraries(2_cinemaLib PRIVATE nlohmann_json::nlohmann_json)
