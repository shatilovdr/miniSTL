cmake_minimum_required (VERSION 3.20)

project(miniSTL VERSION 1.0)
message(STATUS "miniSTL @ ${CMAKE_PROJECT_VERSION}")

add_library(miniSTL INTERFACE)

# Compiler flags interface target
add_library(target_compiler_flags INTERFACE)
target_compile_features(target_compiler_flags INTERFACE cxx_std_20)
target_compile_options(target_compiler_flags INTERFACE -Wextra -Wall -Werror)


target_link_libraries(miniSTL INTERFACE target_compiler_flags)

# Define build type
set(CMAKE_BUILD_TYPE Debug)

# Option to switch between Debug and Release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in DEBUG mode")
    target_compile_definitions(target_compiler_flags INTERFACE DEBUG)
    target_compile_options(target_compiler_flags INTERFACE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building in Release mode")
    target_compile_options(target_compiler_flags INTERFACE -Ofast)
endif()

# Include header files to the project
target_include_directories(miniSTL INTERFACE ${PROJECT_SOURCE_DIR}/miniSTL)

# Add the tests subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)