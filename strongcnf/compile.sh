#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/strongcnf.cpp -o $P/../bin/strongcnf -O3