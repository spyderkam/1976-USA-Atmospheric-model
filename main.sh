#!/bin/bash

echo "Compiling and running the C++ source code..."

# Compile the C++ source code
g++ -o atmosphere src/cpp/main.cpp -lboost_math_c99

# Run the compiled program and then delete the executable
./atmosphere
rm -f atmosphere

printf "%.0s=" {1..60}; printf "\n"

echo "Now running the Python script..."

python src/python/main.py
