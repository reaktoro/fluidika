# Build catch test framework
if(NOT TARGET catch)
    add_library(catch OBJECT catch.hpp catch.cpp)
    set_target_properties(catch PROPERTIES CXX_STANDARD 11)
endif()