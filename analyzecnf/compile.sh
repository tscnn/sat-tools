#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/analyzecnf.cpp -o $P/../bin/analyzecnf -O3