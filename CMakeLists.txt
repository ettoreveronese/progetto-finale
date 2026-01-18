# autore: ettore veronese
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

project(Tutor_Autostrade)

add_library(common_lib STATIC
    common/Gantry.cpp
    common/Highway.cpp
    common/Junction.cpp
    common/Passage.cpp
    common/Vehicle.cpp
)

add_library(simulator_lib STATIC simulator/Simulator.cpp)
target_include_directories(simulator_lib PRIVATE common)

add_library(tutor_lib SHARED tutor/Tutor.cpp)
target_include_directories(tutor_lib PRIVATE common)

add_executable(simulator simulator/main.cpp)
target_include_directories(simulator PRIVATE common simulator)
target_link_libraries(simulator PRIVATE simulator_lib common_lib)

add_executable(tutor tutor/main.cpp)
target_include_directories(tutor PRIVATE common tutor)
target_link_libraries(tutor PRIVATE tutor_lib common_lib)


