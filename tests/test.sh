#!/bin/bash

cd /home/void/Projects/lowg && \
make && \
cd tests && \
./build.sh fonts_lowg.cpp fonts && ./fonts
