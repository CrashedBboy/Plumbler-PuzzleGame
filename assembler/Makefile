#!/bin/sh
CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0`
FILES="*.s layout.c"
clear

echo "* Now starting compilation..."
if $CC $FILES $CFLAGS -o Plumber ; then 
	echo "  Compile completed\n  Execute file 'Plumber' to start game!"
else
	echo "  Error occured while building, please check the source code"
fi
