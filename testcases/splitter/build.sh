#!/bin/bash

mkdir -p in
gcc -c f.c
gcc -c main.c
cat f.c main.c > test.o
mv test.o in
rm f.o main.o

