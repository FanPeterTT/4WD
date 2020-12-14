#!/bin/bash
export DEST="/home/peter/work/Stm32Project/DemoStm32f103/.exvim.demo/"
export TOOLS="/home/peter/.vim/tools/"
export IS_EXCLUDE=
export FOLDERS=""
export FILE_SUFFIXS=".*"
export TMP="${DEST}/_files"
export TARGET="${DEST}/files"
export ID_TARGET="${DEST}/idutils-files"
bash ${TOOLS}/shell/bash/update-filelist.sh
