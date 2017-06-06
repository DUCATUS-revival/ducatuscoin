#!/bin/bash

while true;
do
docker ps -q | while read line ; do docker exec -i $line dctcoin-cli generate 1000 &  done
sleep 1
done
