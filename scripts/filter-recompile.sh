#!/bin/bash

set -e

MYDIR=$(dirname $0)
cd "$MYDIR/../sidplay-libs-2.1.1"

# ensure psiddrv is not recompiled with xa, I don't have it
touch libsidplay/src/psiddrv.bin

# workaround a bug in Debian's packaging scripts
rm -rf debian/libsidplay-dev

# compile
DEB_BUILD_OPTIONS="debug nostrip" MAKEFLAGS=-j3 fakeroot debian/rules binary-arch

# install
cd ..
sudo dpkg -i *.deb
