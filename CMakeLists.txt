# autore: ettore veronese
cmake_minimum_required(VERSION 2.84...3.5)
set(CMAKE_CXX_STANDARD 11)

project(Tutor_Autostrade)

add_subdirectory(common)
add_subdirectory(simulator)
add_subdirectory(tutor)
add_subdirectory(tests)
