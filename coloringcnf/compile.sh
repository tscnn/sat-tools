#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/coloringcnf.cpp -o $P/../bin/coloringcnf -O3
