#!/bin/bash

if [ -z "$1" ]
then
    echo "uso: $0 <login>"
    exit 1;
fi

FILE=$1

mkdir $FILE
cp ./* ./$FILE
rm $FILE/$0 .
ls


tar czvf $FILE.tar.gz $FILE/*
rm -r $FILE
