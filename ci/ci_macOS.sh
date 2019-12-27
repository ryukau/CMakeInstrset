#!/bin/bash
#
# Build script for GitHub Actions.
#

set -e

sysctl -n machdep.cpu.brand_string
system_profiler SPHardwareDataType

cd test || exit
./run.sh

cd .. || exit

mkdir build
cd build || exit

cmake -GXcode ..
cmake --build .

brew install tree
tree --charset ascii

./Debug/test_vcl
