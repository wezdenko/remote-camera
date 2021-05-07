#!/bin/bash

# copying executable files

FOLDER="bin"

if [[ ! -d $FOLDER ]]
then
    mkdir $FOLDER
fi

ConsumerApp="build/consumer/ConsumerApp"
PruducerApp="build/producer/ProducerApp"

if [[ -f $ConsumerApp && -f $PruducerApp ]]
then
    cp $ConsumerApp $FOLDER
    cp $PruducerApp $FOLDER
else
    echo "Build the project first!"
    exit 1
fi

# running app

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

x-terminal-emulator -e "${SCRIPT_DIR}/${FOLDER}/ConsumerApp" ConsumerApp &
x-terminal-emulator -e "${SCRIPT_DIR}/${FOLDER}/ProducerApp" ProducerApp &