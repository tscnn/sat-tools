#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/edpcnf.cpp -o $P/../bin/edpcnf -O3 -std=c++11
