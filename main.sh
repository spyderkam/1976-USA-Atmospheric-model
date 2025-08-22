#!/bin/bash

echo "Compiling and running the C++ source code..."

# Compile the C++ source code
g++ -o atmosphere 1976-USA-Atmosphere/src/cpp/main.cpp -lboost_math_c99

# Run the compiled program
./atmosphere

rm -f atmosphere

printf "%.0s=" {1..60}; printf "\n"

echo "Now running the Python script..."

python 1976-USA-Atmosphere/src/python/main.py