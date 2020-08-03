#!/bin/sh

if [ -f "blogserver" ]; 
    then    rm blogserver
fi

cd build

cmake .. && make

cd ../

if [ -f "blogserver" ]; 
    then    ./blogserver
fi
