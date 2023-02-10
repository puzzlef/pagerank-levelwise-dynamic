#!/usr/bin/env bash
src="pagerank-levelwise-dynamic-validate-skip-unchanged-components"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -O3 main.cxx
stdbuf --output=L ./a.out data/min1c1l.txt 2 2 true  2>&1 | tee -a "$out"
stdbuf --output=L ./a.out data/min2c1l.txt 5 2 true  2>&1 | tee -a "$out"
stdbuf --output=L ./a.out data/min3c3l.txt 13 5 true 2>&1 | tee -a "$out"
stdbuf --output=L ./a.out data/min8c1l.txt 8 5 true 2>&1 | tee -a "$out"
