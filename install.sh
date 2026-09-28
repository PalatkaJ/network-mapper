#!/bin/bash
set -e

if [ -z "$VCPKG_ROOT" ]; then
    echo "Error: VCPKG_ROOT is not set. Download it if necessary and set the env variable.\n See more information about vcpkg here: https://github.com/microsoft/vcpkg"
    exit 1
fi

echo "--- Installing dependencies and configuring project ---"
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

echo "--- Building the project ---"
cmake --build build --config Release

echo "--- Done ---"
