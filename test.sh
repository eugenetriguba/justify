#!/usr/bin/env bash
set -euo pipefail

source ./build.sh

(cd build && ctest --output-on-failure)
./tests/vendor/bats-core/bin/bats ./tests/justify.bats
