
#! /bin/bash

g++-13 -Wall -pedantic -O3 -std=c++20 -fsanitize=address -o main main.cpp
g++-13 -O3 -std=c++20 -fsanitize=address -o simple simple.cpp  ## really simple!
