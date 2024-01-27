#!/bin/bash

# Check if correct number of arguments is passed
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 numA numB"
    exit 1
fi

# Assign command line arguments to numA and numB
numA=$1
numB=$2

# Number of times to run the script
# Set this to a specific number, or use '0' to run indefinitely
NUMBER_OF_RUNS=0

# Counter for the number of runs
count=0

while [ $count -lt $NUMBER_OF_RUNS ] || [ $NUMBER_OF_RUNS -eq 0 ]
do
    echo "Running correctness_check.sh - Attempt $((count+1))"
    ./correctness_check.sh "$numA" "$numB"

    # Increment the counter
    ((count++))
done

echo "Script execution completed."
