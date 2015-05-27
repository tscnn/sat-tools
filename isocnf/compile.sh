#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/isocnf.cpp -o $P/../bin/isocnf -O3
