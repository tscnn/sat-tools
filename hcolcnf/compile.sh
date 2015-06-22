#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/hcolcnf.cpp -o $P/../bin/hcolcnf -O3
