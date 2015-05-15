#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/hgv_cnf.cpp -o $P/../bin/hgv_cnf -O3
