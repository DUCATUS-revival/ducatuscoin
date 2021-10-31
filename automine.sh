#!/bin/bash

rpcport=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcport | cut -c 9-  )
rpcuser=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcuser | cut -c 9-  )
rpcpassword=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcpassword | cut -c 13-  )

# echo "$rpcport $rpcuser $rpcpassword"

while true; do
    ducatuscoin-cli \
      -testnet \
      -rpcconnect=ducatuscoin_node \
      -rpcport=$rpcport \
      -rpcuser=$rpcuser \
      -rpcpassword=$rpcpassword \
      keypoolrefill 1

    ducatuscoin-cli \
      -testnet \
      -rpcconnect=ducatuscoin_node \
      -rpcport=$rpcport \
      -rpcuser=$rpcuser \
      -rpcpassword=$rpcpassword \
      generate 100

    echo "Generated 100, sleep 3s"
    sleep 3
done

