#!/bin/bash
# Main build script for Embedded Learning Platform

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"
INSTALL_DIR="$PROJECT_ROOT/install"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${YELLOW}Building Embedded Learning Platform...${NC}"

# Create build directories
mkdir -p "$BUILD_DIR"
mkdir -p "$INSTALL_DIR"

# Build all applications
cd "$PROJECT_ROOT/applications"

for app_dir in */; do
    if [ -f "$app_dir/CMakeLists.txt" ]; then
        app_name=$(basename "$app_dir")
        echo -e "${GREEN}Building $app_name...${NC}"
        mkdir -p "$BUILD_DIR/$app_name"
        cd "$BUILD_DIR/$app_name"
        cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
              "$PROJECT_ROOT/applications/$app_name"
        make -j$(nproc)
        make install
    fi
done

# Build drivers
cd "$PROJECT_ROOT/drivers"
for driver_dir in */; do
    if [ -f "$driver_dir/Makefile" ]; then
        driver_name=$(basename "$driver_dir")
        echo -e "${GREEN}Building driver: $driver_name...${NC}"
        cd "$driver_dir"
        make -j$(nproc)
        cd ..
    fi
done

echo -e "${GREEN}Build complete!${NC}"
echo -e "Binaries installed to: $INSTALL_DIR"
