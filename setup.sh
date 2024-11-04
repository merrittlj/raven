#!/bin/sh

mkdir -p ./{libs,build}

git submodule update --init
git pull --recurse-submodules
