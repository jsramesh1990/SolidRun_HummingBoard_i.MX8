#!/bin/bash
# Install all systemd services

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
SERVICE_DIR="$PROJECT_ROOT/systemd"

echo "Installing systemd services..."

# Copy service files
for service_file in "$SERVICE_DIR"/*.service; do
    service_name=$(basename "$service_file")
    echo "Installing $service_name..."
    sudo cp "$service_file" /etc/systemd/system/
done

# Reload systemd
sudo systemctl daemon-reload

# Enable services
for service_file in "$SERVICE_DIR"/*.service; do
    service_name=$(basename "$service_file")
    echo "Enabling $service_name..."
    sudo systemctl enable "$service_name"
done

echo "Services installed and enabled."
echo "To start all services: sudo systemctl start dashboard.service"
echo "To check status: sudo systemctl status dashboard.service"
