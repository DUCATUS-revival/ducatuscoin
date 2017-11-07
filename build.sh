#!/bin/bash
DUCATUSD_CONF_FILE=ducatuscoin.conf
RPC_USER=`< /dev/urandom tr -dc A-Za-z0-9 | head -c30` #this generates a random rpc username 
RPC_PASSWORD=`< /dev/urandom tr -dc A-Za-z0-9 | head -c30` #this generates a random rpc password
CON_TOTAL=$(grep MemTotal: /proc/meminfo | awk '($2) {CON_TOTAL=($2/1024/8)+0.5/1} END{printf "%0.f\n", CON_TOTAL}')
echo "Creating the ducatuscoin.conf file"
echo "rpcuser=$RPC_USER" > $DUCATUSD_CONF_FILE
echo "rpcpassword=$RPC_PASSWORD" >> $DUCATUSD_CONF_FILE
echo "rpcallowip=127.0.0.1" >> $DUCATUSD_CONF_FILE
echo "server=1" >> $DUCATUSD_CONF_FILE
echo "daemon=1" >> $DUCATUSD_CONF_FILE
echo "maxconnections=$CON_TOTAL" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-0.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-1.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-2.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-3.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-4.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
echo "addnode=snode-5.p90.ducatus.io" >> $DUCATUSD_CONF_FILE
docker build . -t ducatuscoin-p90x
