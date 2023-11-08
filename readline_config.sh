#!/bin/bash

path="`pwd`/$1"
mkdir -p $path
cd libraries/readline-8.2 && ./configure --prefix=$path
make
make install
