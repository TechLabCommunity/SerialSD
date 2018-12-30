#!/bin/sh

if [ -z "$1" ]; then
    echo "No argument supplied"
    exit 1
fi

printf "get:vers" > $1
sleep 10
printf "get:vers" > $1
sleep 1
printf "ion\n" > $1