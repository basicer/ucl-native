#!/bin/sh
git submodule init
git submodule update
if [ ! -d build ]; then
	mkdir build
	cd build
	cmake -G Ninja ..
	cd ..
fi
ninja -C build
./build/ucl

