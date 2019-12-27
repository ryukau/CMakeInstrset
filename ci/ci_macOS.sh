#!/bin/bash
#
# Build script for GitHub Actions.
#

set -e

mkdir build
cd build || exit

cmake ..
cmake --build .

./test_vcl
