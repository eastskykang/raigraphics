#!/usr/bin/env bash
set -ex

cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_PYTHON=ON ../
make pyraigraphics_build