#!/bin/bash


lib_location=$(find / -name libmemcached)
gcc -o memclient memcached_client.c -I"$lib_location" -lmemcached
echo "Write: ./memclient"
