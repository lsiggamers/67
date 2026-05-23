#!/usr/bin/env bash

set -e

echo "Detecting distro..."

# Detect distro
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    echo "Cannot detect Linux distro!"
    exit 1
fi

echo "Detected: $DISTRO"

# Function to check command exists
command_exists() {
    command -v "$1" &> /dev/null
}

# Install dependencies depending on distro
install_deps() {

    case "$DISTRO" in
        fedora|rhel|centos)
            echo "Using dnf..."
            sudo dnf install -y gcc-c++
            ;;
        ubuntu|debian)
            echo "Using apt..."
            sudo apt install -y g++
            ;;
        arch)
            echo "Using pacman..."
            sudo pacman -Sy --noconfirm gcc
            ;;
        *)
            echo "Unsupported distro: $DISTRO"
            exit 1
            ;;
    esac
}

echo "Checking dependencies..."

NEED_INSTALL=false

# Check g++
if ! command_exists g++; then
    echo "g++ not found"
    NEED_INSTALL=true
fi

if [ "$NEED_INSTALL" = true ]; then
    install_deps
else
    echo "All dependencies already installed"
fi

echo "Compiling..."
g++ cpp_files/*.cpp -o my_program -o AppLauncher -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Ih_files

echo "Running..."
./AppLauncher
