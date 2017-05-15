#!/bin/bash

set -x

COIN_LONG_NAME="dctcoin"
COIN_ABBREVIATION="DCTC"
RPC_PORT=9690

sed -i "s/litecoin/$COIN_LONG_NAME/g" README.md autogen.sh src/*.h src/*.cpp configure.ac
sed -i "s/Litecoin/$COIN_LONG_NAME/g" README.md autogen.sh src/*.h src/*.cpp configure.ac
sed -i "s/LTC/$COIN_ABBREVIATION/g" README.md autogen.sh src/*.h src/*.cpp configure.ac
sed -i "s/9332/$RPC_PORT/g" src/chainparamsbase.cpp src/chainparams.cpp src/rpc/server.cpp
sed -i "s/9333/$(($RPC_PORT + 1 ))/g" src/chainparamsbase.cpp src/chainparams.cpp src/rpc/server.cpp
sed -i "s/9335/$(($RPC_PORT + 2 ))/g" src/chainparamsbase.cpp src/chainparams.cpp src/rpc/server.cpp
rename s/litecoin/$COIN_LONG_NAME/ * src/*
