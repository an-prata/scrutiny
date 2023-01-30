#!/usr/bin/bash

mkdir -p build/
gcc -Wall -Wextra -c scrutiny/scrutiny.c -o build/scrutiny.o
ar rcs build/scrutiny.a build/scrutiny.o

