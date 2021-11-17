#!/bin/bash

rpcport=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcport | cut -c 9-  )
rpcuser=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcuser | cut -c 9-  )
rpcpassword=$(cat /root/.ducatuscoin/ducatuscoin.conf | grep rpcpassword | cut -c 13-  )
walletpassphrase=$(head -1 /root/.node_pwd | grep rpcpassword | cut -c 13-  )

# echo "$rpcport $rpcuser $rpcpassword"

while true; do
    echo "Unlock wallet with passphrase"
    ducatuscoin-cli \
      -testnet \
      -rpcconnect=ducatuscoin_node \
      -rpcport=$rpcport \
      -rpcuser=$rpcuser \
      -rpcpassword=$rpcpassword \
      walletpassphrase $walletpassphrase 1000000
    
    echo "Refill keypool"
    ducatuscoin-cli \
      -testnet \
      -rpcconnect=ducatuscoin_node \
      -rpcport=$rpcport \
      -rpcuser=$rpcuser \
      -rpcpassword=$rpcpassword \
      keypoolrefill 1

    echo "Generate blocks"
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

