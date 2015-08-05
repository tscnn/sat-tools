#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/x3ccnf.cpp -o $P/../bin/x3ccnf -O3
