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

RUN wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
RUN tar -xzvf db-4.8.30.NC.tar.gz
RUN cd db-4.8.30.NC/build_unix \
	../dist/configure --enable-cxx --prefix=/usr \
	make -j8 \
	make install 

# install bitcoind (from PPA) and make
RUN apt-get install --yes make pkg-config bsdmainutils

# create a non-root user
RUN adduser --disabled-login --gecos "" ducatus

# run following commands from user's home directory
WORKDIR /home/ducatus

# copy the testnet-box files into the image
ADD . /home/ducatus/dctcoin
WORKDIR /home/ducatus/dctcoin

RUN ./autogen.sh
RUN aclocal
RUN ./autogen.sh
RUN autoreconf -i
RUN autoconf
RUN ./configure --with-incompatible-bdb
RUN make
RUN make -j 5 install
RUN mkdir /home/ducatus/dctcoin-tumbler

# make ducatus user own the bitcoin-testnet-box
RUN chown -R ducatus:ducatus /home/ducatus

# use the ducatus user when running the image
USER ducatus

# run commands from inside the testnet-box directory
WORKDIR /home/ducatus/dctcoin-tumbler

# expose two rpc ports for the nodes to allow outside container access
EXPOSE 19001 19011
CMD ["/bin/bash"]
