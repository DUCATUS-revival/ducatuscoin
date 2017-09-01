#!/bin/bash

while true;
do
sudo docker ps -q | while read line ; do sudo docker exec -i $line ducatuscoin-cli generate 1000 ;  done
done
