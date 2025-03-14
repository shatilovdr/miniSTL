# Create the test executable
add_executable(test test.cpp)

# Link the miniSTL library to the test executable
target_link_libraries(test PRIVATE miniSTL)

# Set output directory for the executable
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
