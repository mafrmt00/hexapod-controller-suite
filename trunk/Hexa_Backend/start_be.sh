#!/bin/bash

outpipe=/tmp/hexa_be_out
inpipe=/tmp/hexa_be_in
serialport=/dev/ttyO0 

#Initialize Serial Port
stty -F $serialport 115200 cs8 -cstopb -parity -icanon min 100 time 1

trap "rm -f $outpipe" EXIT
trap "rm -f $inpipe" EXIT

if [[ ! -p $inpipe ]]; then
    mkfifo $inpipe
fi

if [[ ! -p $outpipe ]]; then
    mkfifo $outpipe
fi


./Debug/Hexa_Backend

echo "Hexa Backend exiting"