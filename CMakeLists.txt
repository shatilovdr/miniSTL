cmake_minimum_required (VERSION 3.20)

project(test)
message(STATUS "test @ ${CMAKE_PROJECT_VERSION}")
add_executable(test)

# Compiler flags interface target
add_library(target_compiler_flags INTERFACE)
target_compile_features(target_compiler_flags INTERFACE cxx_std_20)
target_compile_options(target_compiler_flags INTERFACE -Wextra -Wall -Werror)
target_link_libraries(test PUBLIC target_compiler_flags)

# Option to switch between Debug and Release
option(DEBUG "Enable Debug mode" ON)
if(DEBUG)
    message(STATUS "Building in DEBUG mode")
    # target_compile_definitions(target_compiler_flags INTERFACE DEBUG)
    # target_compile_options(target_compiler_flags INTERFACE -g)
else()
    message(STATUS "Building in Release mode")
    # target_compile_options(target_compiler_flags INTERFACE -Ofast)
endif()

add_subdirectory(ministl)
target_link_libraries(test PUBLIC ministl)

target_sources(test PRIVATE main.cpp)