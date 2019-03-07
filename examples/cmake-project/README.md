
# CMake-Based Project Using Fluidika

## Introduction

This example demonstrates how CMake's command `find_package` can be used to
resolve the dependency of an executable `app` on **Fluidika**, a C++17 library
for calculation of thermophysical properties of fluids.

The source file `main.cpp` includes the header-file `Fluidika/Fluidika.hpp`
and uses the Wagner and Pruss (2002) equation of state to compute thermodynamic
properties of water.

The `CMakeLists.txt` file uses the command:

```cmake
find_package(Fluidika REQUIRED)
```

to find the **Fluidika** package. The executable target `app` is then linked
against the imported target `Fluidika::Fluidika`:

```cmake
target_link_libraries(app Fluidika::Fluidika)
```

## Building and Executing the Application

To build the application, do:

```bash
cd cmake-project
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Fluidika/install/dir
make
```

To execute the application, do:

```bash
./app
```

Note: If **Fluidika** has been installed system-wide, then the CMake argument
`CMAKE_PREFIX_PATH` should not be needed. Otherwise, you will need to specify
where **Fluidika** is installed in your machine. For example:

```cmake
cmake .. -DCMAKE_PREFIX_PATH=$HOME/local
```

assuming directory `$HOME/local` is where **Fluidika** was installed to, which
should then contain the following directory:

```
$HOME/local/include/Fluidika/
```

where the **Fluidika** header files are located.
