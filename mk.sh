#!/bin/sh

rm main

cd build

cmake .. && make

cd ../

if [ -f "main" ]; 
    then    ./main
fi
