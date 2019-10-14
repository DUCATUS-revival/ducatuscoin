#!/bin/bash

set -x

COIN_LONG_NAME="ducatuscoin"
COIN_ABBREVIATION="DUC"

sed -i "s/dctcoin/$COIN_LONG_NAME/g" README.md autogen.sh src/*.h src/*.cpp configure.ac
sed -i "s/DTC/$COIN_ABBREVIATION/g" README.md autogen.sh src/*.h src/*.cpp configure.ac
rename s/dctcoin/$COIN_LONG_NAME/ * src/*
