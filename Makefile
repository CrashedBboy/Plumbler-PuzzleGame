#!/bin/sh
CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0`
ENTRY=src/main.c

clear

if [ -f $ENTRY ] ; then
	$CC $ENTRY $CFLAGS -o PowerEngineer.exe
else
	echo "====================="
	echo "File main.c Not Found"
	echo "====================="
fi