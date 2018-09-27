# Collect all header files from the current directory for the C++ library
file(GLOB_RECURSE HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

# Collect all source files from the current directory for the C++ library
file(GLOB_RECURSE CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Collect all test source files from the current directory for the C++ testing suite
file(GLOB_RECURSE CXX_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.test.cxx)

# The name of the shared and static libraries
set(PROJECT_SHARED_LIB ${PROJECT_NAME}${SUFFIX_SHARED_LIBS})
set(PROJECT_STATIC_LIB ${PROJECT_NAME}${SUFFIX_STATIC_LIBS})

# Compile the cpp files into object files
add_library(FluidikObject OBJECT ${HPP_FILES} ${CPP_FILES})

# Add the root path of this project to the cmake include directories
target_include_directories(FluidikObject PUBLIC ${PROJECT_SOURCE_DIR})

# Set some properties for the FluidikObject target
set_property(TARGET FluidikObject PROPERTY POSITION_INDEPENDENT_CODE ON)

# Ensure Fluidik is compiled with a compiler that supports C++11
set_property(TARGET FluidikObject PROPERTY CXX_STANDARD 11)

# Check if a shared library for Fluidik must be built
if(BUILD_SHARED_LIBS)
    add_library(FluidikShared SHARED $<TARGET_OBJECTS:FluidikObject>)
    set_target_properties(FluidikShared PROPERTIES OUTPUT_NAME Fluidik)
    install(TARGETS FluidikShared DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries)
endif()

# Check if a static library for Fluidik must be built
if(BUILD_STATIC_LIBS)
    add_library(FluidikStatic STATIC $<TARGET_OBJECTS:FluidikObject>)
    set_target_properties(FluidikStatic PROPERTIES OUTPUT_NAME Fluidik)
    install(TARGETS FluidikStatic DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries)
endif()

# Create an install target for Fluidik header files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Fluidik
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers
    FILES_MATCHING PATTERN "*.hpp")
    
# Build the test application
add_executable(FluidikTests ${CXX_FILES} $<TARGET_OBJECTS:catch>)
set_target_properties(FluidikTests PROPERTIES CXX_STANDARD 11)
target_include_directories(FluidikTests PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(FluidikTests PUBLIC ${PROJECT_SOURCE_DIR}/deps)
target_link_libraries(FluidikTests FluidikShared)