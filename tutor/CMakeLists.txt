add_executable(tutor main.cpp Tutor.cpp)

target_include_directories(tutor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tutor PRIVATE common)
