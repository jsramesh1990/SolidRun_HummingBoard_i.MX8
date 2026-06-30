#!/bin/bash
# Monitor all services and restart if they fail

set -e

while true; do
    for service in dashboard calculator data-structures gpio i2c spi uart can mqtt sensors logger database camera; do
        if ! systemctl is-active --quiet "${service}.service"; then
            echo "Service $service is not running. Restarting..."
            sudo systemctl restart "${service}.service"
        fi
    done
    sleep 10
done
