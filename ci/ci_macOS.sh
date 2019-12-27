#!/bin/bash
#
# Build script for GitHub Actions.
#

set -e

sysctl -n machdep.cpu.brand_string
system_profiler SPHardwareDataType

mkdir build
cd build || exit

cmake -GXcode ..
cmake --build .

./test_vcl
