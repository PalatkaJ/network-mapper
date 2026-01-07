#!/bin/bash

OS=$(uname -s)

if [ "$OS" == "Darwin" ]; then
    INTERFACE=$(route -n get default | grep 'interface:' | grep -o '[^ ]*$') 
else 
    INTERFACE=$(ip route 2>/dev/null | grep '^default' | awk '{print $5}' | head -n1)
    
    if [ -z "$INTERFACE" ]; then
        INTERFACE=$(route -n 2>/dev/null | grep '^0.0.0.0' | awk '{print $8}' | head -n1)
    fi
fi

echo "--- Running demo using interface: $INTERFACE ---"
sudo ./build/network-mapper --interface "$INTERFACE"
