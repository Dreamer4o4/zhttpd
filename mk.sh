#!/bin/sh

if [ -f "server" ]; 
    then    rm server
fi

cd build

cmake .. && make

cd ../

if [ -f "server" ]; 
    then    ./server
fi
