#!/bin/bash
# Build script for Unit Converter project

set -e

echo "=== Unit Converter - Build Script ==="
echo ""

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Setting up Meson build system..."
    meson setup build
fi

echo "Building project with Ninja..."
ninja -C build

echo ""
echo "Build complete! Run tests with:"
echo "  ninja -C build test"
echo ""
echo "Run the converter with:"
echo "  ./build/Convertisseur \"convert 1.3 kg to lb\""
