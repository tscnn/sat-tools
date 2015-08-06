#!/bin/bash
P=${0%/*}
mkdir -p "$P/../bin"
g++ $P/schoening.cpp -o $P/../bin/schoening-static -O3 -static -lgmp -fopenmp
g++ $P/schoening.cpp -o $P/../bin/schoening-static64 -O3 -static -lgmp -fopenmp -m64
g++ $P/schoening.cpp -o $P/../bin/schoening-static32 -O3 -static -lgmp -fopenmp -m32
g++ $P/schoening.cpp -o $P/../bin/schoening -O3 -lgmp -fopenmp
