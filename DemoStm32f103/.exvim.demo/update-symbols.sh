#!/bin/bash
export DEST="/home/peter/work/Stm32Project/DemoStm32f103/.exvim.demo/"
export TOOLS="/home/peter/.vim/tools/"
export TMP="${DEST}/_symbols"
export TARGET="${DEST}/symbols"
sh ${TOOLS}/shell/bash/update-symbols.sh
