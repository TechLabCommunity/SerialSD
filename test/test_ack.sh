#!/bin/sh

if [ -z "$1" ]; then
    echo "No argument supplied"
    exit 1
fi

printf "ack:ciao mi ritorni qualcosa?\n" > $1
sleep 1
printf "ACK:taci\n" > $1
sleep 1
printf "ack:AAAAAAAAAAAAAAAAAAAAAAAAAAAAA:AAAAAA::::AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n" > $1
sleep 1