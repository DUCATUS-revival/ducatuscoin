# bitcoin-testnet-box docker image

# Ubuntu 14.04 LTS (Trusty Tahr)
FROM ubuntu:14.04

# add bitcoind from the official PPA
RUN apt-get update
RUN apt-get install -y ntp git build-essential libssl-dev libdb-dev libdb++-dev libboost-all-dev libqrencode-dev
RUN apt-get install -y libevent-dev
RUN apt-get install -y autoconf
RUN apt-get install -y libtool
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y wget
RUN apt-get install -y software-properties-common python-software-properties
RUN add-apt-repository -y ppa:bitcoin/bitcoin
RUN apt-get update -y
RUN apt-get install -y bitcoind git
RUN apt-get install -y libdb4.8-dev libdb4.8++-dev

RUN wget https://github.com/jgarzik/univalue/releases/download/v1.0.4/univalue-1.0.4.tar.gz; \
	tar xvzf univalue-1.0.4.tar.gz: \
	cd univalue-1.0.4; \
	./autogen.sh; \
	./configure; \
	make install

# install bitcoind (from PPA) and make
RUN apt-get install --yes make pkg-config bsdmainutils
RUN apt-get install -y libminiupnpc-dev 
RUN apt-get install -y libzmq3-dev
RUN apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

# create a non-root user
RUN adduser --disabled-login --gecos "" ducatus

# run following commands from user's home directory
WORKDIR /root

# copy the testnet-box files into the image
ADD . /root/ducatuscoin
WORKDIR /root/ducatuscoin

RUN git clean -fdx
RUN ./autogen.sh
RUN aclocal
RUN ./autogen.sh
RUN autoreconf -i
RUN autoconf
RUN ./configure --with-system-univalue --with-gui=no --with-qrencode=no --disable-tests
RUN make
RUN make -j 5 install
RUN mkdir -p /root/ducatuscoin-tumbler
RUN mkdir -p /root/.ducatuscoin/
ADD ./ducatuscoin.conf /root/.ducatuscoin/

# expose two rpc ports for the nodes to allow outside container access
EXPOSE 9690 9691
CMD ["/bin/bash"]
