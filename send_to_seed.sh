#!/bin/bash

sudo docker ps -q | while read line 
do 
	echo $line
	#docker cp sleep-test.sh $line:/usr/local/bin/ducatuscoin-cli
	docker exec -i $line chmod +x /usr/local/bin/ducatuscoin-cli
done
