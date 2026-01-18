#Autore: Tommaso Polo
add_executable(simulator main.cpp Simulator.cpp)

target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(simulator PRIVATE common)
