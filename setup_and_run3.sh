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

install_deps() {

    case "$DISTRO" in
        fedora|rhel|centos)
            echo "Using dnf..."
            sudo dnf install -y \
                gcc-c++ \
                raylib-devel \
                mesa-libGL-devel \
                libX11-devel
            ;;

        ubuntu|debian)
            echo "Using apt..."
            sudo apt update
            sudo apt install -y \
                g++ \
                libraylib-dev \
                libgl1-mesa-dev \
                libx11-dev
            ;;

        arch)
            echo "Using pacman..."
            sudo pacman -Sy --noconfirm \
                gcc \
                raylib \
                mesa \
                libx11
            ;;

        *)
            echo "Unsupported distro: $DISTRO"
            exit 1
            ;;
    esac
}

echo "Checking dependencies..."

NEED_INSTALL=false

# Core compiler check
if ! command_exists g++; then
    echo "g++ not found"
    NEED_INSTALL=true
fi

# Raylib check (important fix)
if ! ldconfig -p 2>/dev/null | grep -q raylib; then
    echo "raylib not found"
    NEED_INSTALL=true
fi

if [ "$NEED_INSTALL" = true ]; then
    install_deps
else
    echo "All dependencies already installed"
fi

echo "Compiling..."

g++ cpp_files/*.cpp \
    -o AppLauncher \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -Ih_files

echo "Running..."
./AppLauncher