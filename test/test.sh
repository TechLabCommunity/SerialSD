#!/bin/sh

if [ -z "$1" ]; then
    echo "No argument supplied"
    exit 1
fi

printf "get:euro_price_0\n" > $1
sleep 1
printf "get:euro_price_0\n" > $1
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
printf "\n" > $1
sleep 1
printf "rfgr3gf:version\n" > $1
sleep 1
printf "wefgergfre:version\n" > $1
sleep 1
printf ":version\n" > $1
sleep 1
printf "log:nuovo log questa prova\n" > $1
sleep 1
printf "log:sdfat is great\n" > $1
sleep 1
printf "log:happy new year\n" > $1
sleep 1
