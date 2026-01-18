# Autore : Paolo Gasparato
add_library(common
    Gantry.cpp
    Highway.cpp
    Junction.cpp
    Passage.cpp
    Vehicle.cpp
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
