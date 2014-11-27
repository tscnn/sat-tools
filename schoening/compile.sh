#!/bin/bash
P=${0%/*}
mkdir "$P/../bin"
g++ $P/schoening.cpp -o $P/../bin/schoening -O3 -lgmp -fopenmp
