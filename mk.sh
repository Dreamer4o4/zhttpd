#!/bin/sh

rm server

cd build

cmake .. && make

cd ../

if [ -f "server" ]; 
    then    ./server
fi
