#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
SRC_DIR="."

cmake -B "$BUILD_DIR" -S "$SRC_DIR" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$BUILD_DIR"
