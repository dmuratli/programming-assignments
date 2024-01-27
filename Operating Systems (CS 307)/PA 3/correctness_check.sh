#!/bin/bash

# Check if correct number of arguments is passed
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 numA numB"
    exit 1
fi

# Assign command line arguments to numA and numB
numA=$1
numB=$2

# Compile your C++ program
g++ -o rideshare rideshare.cpp -lpthread

# Run your C++ program and store the output in a temporary file
temp_file=$(mktemp)
./rideshare "$numA" "$numB" > "$temp_file"

# Count the number of init, mid, and end strings
num_init=$(grep -c 'I am looking for a car' "$temp_file")
num_mid=$(grep -c 'I have found a spot in a car' "$temp_file")
num_end=$(grep -c 'I am the captain and driving the car with ID' "$temp_file")

# Check conditions
if [ $((numA + numB)) -ne $num_init ]; then
    echo "Error: The number of init strings is not correct."
    cat "$temp_file"
    rm "$temp_file"
    exit 1
fi

if [ $((numA + numB)) -ne $num_mid ]; then
    echo "Error: The number of mid strings is not correct."
    cat "$temp_file"
    rm "$temp_file"
    exit 1
fi

if [ $(((numA + numB) / 4)) -ne $num_end ]; then
    echo "Error: The number of end strings is not correct."
    cat "$temp_file"
    rm "$temp_file"
    exit 1
fi

echo "All checks passed successfully."

# Remove the temporary file
rm "$temp_file"