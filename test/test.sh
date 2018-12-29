#!/bin/sh

if [ -z "$1" ]; then
    echo "No argument supplied"
    exit 1
fi

printf "get:version\n" > $1
sleep 1
printf "get:version\n" > $1
sleep 1
printf "get:euro_price\n" > $1
sleep 1
printf "get:dummy\n" > $1
sleep 1
printf "get:dummy\n" > $1
sleep 1
printf "get:dummy\n" > $1
sleep 1
printf "post:version\n" > $1
sleep 1
printf "get\n" > $1
sleep 1
printf "" > $1
sleep 1
printf "get:version\n" > $1
sleep 1