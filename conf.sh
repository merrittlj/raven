#!/bin/sh

mkdir -p build

git submodule update --init
git pull --recurse-submodules
