#!/bin/bash

outpipe=/tmp/hexa_be_out
inpipe=/tmp/hexa_be_in

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