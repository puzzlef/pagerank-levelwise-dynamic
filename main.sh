#!/usr/bin/env bash
src="pagerank-levelwise-skip-unchanged-components"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -O3 main.cxx
stdbuf --output=L ./a.out data/min1c1l.txt 2 2 true 2>&1 | tee -a "$out"
