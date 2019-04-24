#!/bin/sh
CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0 cairo`
ENTRY=src/main.c

clear

if [ -f $ENTRY ] ; then
	$CC $ENTRY $CFLAGS -o Power\ Engineer
else
	echo "====================="
	echo "File main.c Not Found"
	echo "====================="
fi