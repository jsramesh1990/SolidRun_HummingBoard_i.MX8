#!/bin/bash
# Service management script

set -e

COMMAND="$1"
SERVICE="${2:-all}"

if [ -z "$COMMAND" ]; then
    echo "Usage: $0 {start|stop|restart|status|enable|disable} [service-name]"
    echo "Examples:"
    echo "  $0 start dashboard"
    echo "  $0 status all"
    exit 1
fi

# List of services
SERVICES=(
    dashboard
    calculator
    data-structures
    gpio
    i2c
    spi
    uart
    can
    mqtt
    sensors
    logger
    database
    camera
)

# Function to manage a service
manage_service() {
    local service_name="$1"
    local service_file="${service_name}.service"
    
    if [ ! -f "/etc/systemd/system/$service_file" ]; then
        echo "Warning: $service_file not found"
        return 1
    fi
    
    case $COMMAND in
        start)
            sudo systemctl start "$service_file"
            ;;
        stop)
            sudo systemctl stop "$service_file"
            ;;
        restart)
            sudo systemctl restart "$service_file"
            ;;
        status)
            sudo systemctl status "$service_file"
            ;;
        enable)
            sudo systemctl enable "$service_file"
            ;;
        disable)
            sudo systemctl disable "$service_file"
            ;;
        *)
            echo "Unknown command: $COMMAND"
            return 1
            ;;
    esac
}

# Manage services
if [ "$SERVICE" = "all" ]; then
    for service in "${SERVICES[@]}"; do
        echo "=== $service ==="
        manage_service "$service"
        echo
    done
else
    manage_service "$SERVICE"
fi
