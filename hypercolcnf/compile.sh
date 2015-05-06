#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/hypercolcnf.cpp -o $P/../bin/hypercolcnf -O3
