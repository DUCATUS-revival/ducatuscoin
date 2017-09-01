#!/bin/bash


CONTAINERS=($(sudo docker ps -q))
for i in "${CONTAINERS[@]}"
do
   sudo docker exec -i $i ducatuscoin-cli getinfo
done
