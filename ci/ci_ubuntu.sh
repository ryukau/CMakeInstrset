#!/bin/bash
#
# Build script for GitHub Actions.
#

set -e

lscpu

cd test || exit
./run.sh

cd .. || exit

mkdir build
cd build || exit

cmake ..
cmake --build .

tree

./test_vcl
