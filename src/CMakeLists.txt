cmake_minimum_required(VERSION 3.2)
find_package(Boost 1.65 COMPONENTS program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_library(bn
    lib.cpp
    )
set_target_properties(bn PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(bn LINK_PUBLIC ${Boost_LIBRARIES})
