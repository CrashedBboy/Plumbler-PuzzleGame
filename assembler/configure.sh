#!/bin/sh
PKG_GCC=$(dpkg-query -W --showformat='${Status}\n' gcc|grep "install ok installed")
PKG_GTK=$(dpkg-query -W --showformat='${Status}\n' libgtk-3-dev|grep "install ok installed")

echo "* Check if 'gcc' is installed ..."
if [ "" = "$PKG_GCC" ] ; then
	echo "  gcc assembler not found"
	echo "  Try 'sudo apt-get install gcc' in ubuntu"
else
	echo "  OK"
fi
echo "* Check if 'libgtk-3-dev' is installed ..."
if [ "" = "$PKG_GTK" ] ; then
	echo "  Library 'gtk' not found"
	echo "  Try 'sudo apt-get install libgtk-3-dev' in ubuntu"
else
	echo "  OK"
fi
