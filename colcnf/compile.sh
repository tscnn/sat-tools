#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/colcnf.cpp -o $P/../bin/colcnf -O3
