add_library(ministl STATIC
    src/list.cpp
    src/vector.cpp
)

target_include_directories(ministl PUBLIC inc )
