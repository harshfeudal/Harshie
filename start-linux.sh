#!/bin/bash

# Check if the build directory exists, and if not, create it
if [ ! -d "build" ]; then
    mkdir build
fi

# Change to the build directory
cd build

# Run CMake to generate build files
cmake ..
make -j8

# Check if the compilation was successful, then run
if [ $? -eq 0 ]; then
    ./Harshie
else
    echo "Compilation failed. Please check for errors."
fi
