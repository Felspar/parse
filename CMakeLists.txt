cmake_minimum_required(VERSION 3.10)
project(felspar-parse)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_custom_target(felspar-check)
    set_property(TARGET felspar-check PROPERTY EXCLUDE_FROM_ALL TRUE)
    add_custom_target(felspar-examples)
    include(requirements.cmake)
endif()

add_library(felspar-parse INTERFACE)
target_include_directories(felspar-parse INTERFACE ./include)
target_compile_features(felspar-parse INTERFACE cxx_std_20)
target_link_libraries(felspar-parse INTERFACE felspar-coro felspar-exceptions felspar-test)

add_subdirectory(test)
