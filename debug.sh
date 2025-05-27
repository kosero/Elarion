#!/bin/bash
export DEBUG=1
mkdir -p build &&
cd build &&
cmake .. &&
make -j$(nproc) &&
cd .. &&
./Elarion &&
rm -r Elarion build
