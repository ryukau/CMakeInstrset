#
# Build script for GitHub Actions.
#

$ErrorActionPreference = "Stop"

Get-WmiObject win32_processor

mkdir build
cd build
cmake -G"Visual Studio 16 2019" ..
cmake --build . --config Release

tree /a /f .

& "Release\test_vcl.exe"
