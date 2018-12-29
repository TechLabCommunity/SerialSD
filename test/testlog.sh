#!/bin/sh

if [ -z "$1" ]; then
    echo "No argument supplied"
    exit 1
fi

printf "log:questa e una prova per inserire nel log una frase.\n" > $1
sleep 1
printf "log:questa é una prova con l'accento.\n" > $1
sleep 1
