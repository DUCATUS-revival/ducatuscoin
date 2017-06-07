#!/bin/bash

DEST=192.168.1.191

mkdir -p ~/wallets/

sudo docker ps -q | while read line 
do 
	apt-get install -y sshpass
	ID=$(uuidgen)
	sudo docker exec -i $line cp -R ~/.ducatus/ ~/$ID
	sudo docker exec -i $line sshpass -p "password" scp -r noah@$DEST:~/wallets/ ~/$ID
done


