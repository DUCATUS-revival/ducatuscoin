#!/bin/bash

mkdir -p ~/wallets/

sudo docker ps -q | while read line 
do 
	ID=$(uuidgen)
	echo $line : $ID
	docker cp $line:/home/ducatus/.ducatuscoin/ ~/wallets/$ID
done


