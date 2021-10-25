#!/bin/bash

sudo apt-get update
sudo apt-get install -y ntp git build-essential libssl-dev libdb-dev libdb++-dev libboost-all-dev libqrencode-dev
sudo apt-get install -y libevent-dev
sudo apt-get install -y autoconf
sudo apt-get install -y libtool
sudo apt-get install -y libboost-all-dev
sudo apt-get install -y wget
sudo apt-get install -y software-properties-common python-software-properties
sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get update -y
sudo apt-get install -y bitcoind git
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

git clone https://github.com/jgarzik/univalue; \
	cd univalue; \
	./autogen.sh; \
	./configure; \
	sudo make install

cd ..

sudo apt-get install --yes make pkg-config bsdmainutils
sudo apt-get install -y libminiupnpc-dev 
sudo apt-get install -y libzmq3-dev
sudo apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

./autogen.sh
aclocal
./autogen.sh
autoreconf -i
autoconf
./configure --with-system-univalue 
make
sudo make -j 5 install

