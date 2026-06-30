#!/bin/bash
# SDK generation script

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
SDK_DIR="$PROJECT_ROOT/sdk"

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${YELLOW}Generating SDK...${NC}"

mkdir -p "$SDK_DIR"

cd "$PROJECT_ROOT/yocto"
source sources/poky/oe-init-build-env build

echo -e "${YELLOW}Generating SDK...${NC}"
bitbake -c populate_sdk core-image-minimal

echo -e "${GREEN}SDK generated successfully!${NC}"
echo -e "${YELLOW}SDK location: build/tmp/deploy/sdk/${NC}"
