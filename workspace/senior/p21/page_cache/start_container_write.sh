#!/bin/bash

docker stop page_cache_write;docker rm page_cache_write

if [ ! -f ./data.txt ]
then
	touch data.txt
	echo "Please run start_container.sh again "
	exit 0
fi

docker run -d --init --name page_cache_write -v $(pwd):/mnt youngpig/page_cache_test:v2
CONTAINER_ID=$(sudo docker ps --format "{{.ID}}\t{{.Names}}" | grep -i page_cache_write | awk '{print $1}')

echo $CONTAINER_ID
CGROUP_CONTAINER_PATH=$(find /sys/fs/cgroup/memory/ -name "*$CONTAINER_ID*")
echo 104857600 > $CGROUP_CONTAINER_PATH/memory.limit_in_bytes
cat $CGROUP_CONTAINER_PATH/memory.limit_in_bytes
