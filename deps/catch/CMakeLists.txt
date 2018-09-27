# Build catch test framework
add_library(catch OBJECT catch.hpp catch.cpp)
set_target_properties(catch PROPERTIES CXX_STANDARD 11)