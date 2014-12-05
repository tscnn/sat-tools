#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/randomcnf.cpp -o $P/../bin/randomcnf -O3