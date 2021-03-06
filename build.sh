#!/bin/bash
set -e
CC="g++ -Wall -std=c++17"
mkdir target -p

$CC image.cpp  -c -o target/image.o
$CC vec3.cpp  -c -o target/vec3.o
$CC geom.cpp  -c -o target/geom.o
$CC camera.cpp  -c -o target/camera.o
$CC scene.cpp  -c -o target/scene.o
$CC light.cpp  -c -o target/light.o
$CC ray.cpp  -c -o target/ray.o

OBJ="target/ray.o target/camera.o target/vec3.o target/light.o target/scene.o target/image.o target/geom.o"
$CC test.cpp  -c -o target/test.o
$CC $OBJ target/test.o -o target/test
./target/test

$CC main.cpp  -c -o target/main.o
$CC $OBJ target/main.o -o raytracer
./raytracer
