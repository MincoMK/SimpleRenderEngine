#!/bin/bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cd build
make -j
cd ..
