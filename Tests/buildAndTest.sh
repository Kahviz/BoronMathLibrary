#!/bin/bash
# Placeholder script for building and testing boron math lib

# Make sure this is the root directory
if [ $(basename $PWD) != "BoronMathLibrary" ]; then
    echo "This is not the root directory."
    exit 1
fi

# Build
mkdir -p build
cd build
rm BoronMathLibrary
cmake ../
cmake --build .
./BoronMathLibrary
