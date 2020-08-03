#!/bin/sh

if [ -f "blogserver" ]; 
    then    rm blogserver
fi

if [ ! -d "./build" ]; 
    then    mkdir ./build
fi

cd build

cmake .. && make

cd ../

if [ -f "blogserver" ]; 
    then    ./blogserver
fi
