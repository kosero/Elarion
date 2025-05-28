#!/bin/bash
export CC=clang &&
export CXX=clang++ &&
export DEBUG=1 &&
mkdir -p build &&
cd build &&
cmake .. &&
make -j$(nproc) &&
./Elarion &&
rm Elarion &&
rm -r ../build
