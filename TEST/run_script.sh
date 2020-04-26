#!/bin/bash


#lib_location=$(find / -name libmemcached)
gcc -o memclient memcached_client.c -I/usr/include/libmemcached -lmemcached
echo "Build complete. To execute enter: ./memclient"
