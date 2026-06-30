#!/bin/bash
# Flash script for HummingBoard i.MX8

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Check if device is specified
if [ -z "$1" ]; then
    echo -e "${RED}Usage: $0 <device> [image-file]${NC}"
    echo -e "${YELLOW}Example: $0 /dev/sdb yocto/build/tmp/deploy/images/hummingboard/console-image.sdcard${NC}"
    exit 1
fi

DEVICE="$1"
IMAGE_FILE="${2:-yocto/build/tmp/deploy/images/hummingboard/console-image.sdcard}"

echo -e "${YELLOW}Flashing to $DEVICE...${NC}"

# Check if device exists
if [ ! -b "$DEVICE" ]; then
    echo -e "${RED}Device $DEVICE does not exist${NC}"
    exit 1
fi

# Check if image file exists
if [ ! -f "$IMAGE_FILE" ]; then
    echo -e "${RED}Image file $IMAGE_FILE does not exist${NC}"
    echo -e "${YELLOW}Build the image first with Yocto${NC}"
    exit 1
fi

# Flash the image
echo -e "${YELLOW}Writing image to $DEVICE...${NC}"
sudo dd if="$IMAGE_FILE" of="$DEVICE" bs=4M status=progress
sync

echo -e "${GREEN}Flash complete!${NC}"
echo -e "${YELLOW}Insert SD card into HummingBoard and power on${NC}"
