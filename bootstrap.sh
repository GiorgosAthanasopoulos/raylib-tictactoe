#!/usr/bin/env bash

#Install dependencies
sudo apt install git # in case you downloaded zip from github and dont have git installed
sudo apt install build-essential # gcc make etc.
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev # raylib deps

#Clone and build raylib
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED # To make the dynamic shared version.
sudo make install RAYLIB_LIBTYPE=SHARED # Dynamic shared version.
cd ../../
rm -rf raylib

#Clone and run game
cc nobuild.c -o nobuild
./nobuild
