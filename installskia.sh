#!/bin/bash
mkdir -p skia
cd skia
../node_modules/depot_tools/tools/gclient config --name .  https://skia.googlesource.com/skia.git
../node_modules/depot_tools/tools/gclient sync
./gyp_skia
../node_modules/depot_tools/tools/ninja -C out/Debug
cp ../binding.gyp gyp/binding.gyp
cd gyp
pwd
node-gyp rebuild
