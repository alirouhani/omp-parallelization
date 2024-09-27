#!/bin/bash

export OMP_PLACES=threads
export OMP_PROC_BIND=spread

clang++ -fopenmp main.cpp 
./a.out > screening.log 2>&1
