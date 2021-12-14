
FROM rnbdeploy/ducatuscoin-base:latest

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
# ADD ./ducatuscoin.conf /root/.ducatuscoin/
# ADD ./ducatuscoin.conf /root/

# VOLUME /root/.ducatuscoin

# expose two rpc ports for the nodes to allow outside container access
EXPOSE 9690 9691
#CMD ["/bin/bash"]
CMD ["/bin/bash", "/root/docker-start-point.sh"]
