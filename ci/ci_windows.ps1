#
# Build script for GitHub Actions.
#

$ErrorActionPreference = "Stop"

gwmi -query "SELECT Name FROM Win32_Processor"

mkdir build
cd build
cmake -G"Visual Studio 16 2019" ..
cmake --build . --config Release

tree /a /f .

& "Release\test_vcl.exe"
