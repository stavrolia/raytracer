#!/bin/bash
set -e
CC="g++ -Wall -std=c++17"
mkdir target -p

$CC image.cpp  -c -o target/image.o

$CC test.cpp  -c -o target/test.o
$CC target/image.o target/test.o -o target/test
./target/test

$CC main.cpp  -c -o target/main.o
$CC target/image.o target/main.o -o raytracer
./raytracer
