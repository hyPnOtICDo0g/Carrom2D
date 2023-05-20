#!/bin/bash

# Install Build dependencies

sudo apt install freeglut3 freeglut3-dev -y

# Build linux binary

make -B -j $(nproc)
cd bin && sha256sum Carrom2D-linux-x86_64 > Carrom2D-linux-x86_64.sha256
