#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

! [[ -d build ]] && mkdir build
cd build || exit -1
cmake ..
make "$@"
