#!/bin/bash

clang++ -fopenmp main.cpp 
./a.out > screening.log 2>&1
