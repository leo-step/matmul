#!/bin/bash

python="python3.10"

if [ -z "$1" ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

echo "Running version $1"

if [ "$1" -eq 0 ]; then
  $python mul0.py
else
  gcc -O3 mul$1.c matrix.c main.c -o mul$1 && ./mul"$1" && rm mul$1
fi

