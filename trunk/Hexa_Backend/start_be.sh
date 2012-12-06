#!/bin/bash

pipe=/tmp/hexa_be_out

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

./Debug/Hexa_Backend

echo "Hexa Backend exiting"