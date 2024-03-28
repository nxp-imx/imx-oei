#!/bin/bash

usage()
{
	echo "$0 <board> <oei>"
	echo "board:  eg. mx95lp5, mx95lp4x, mx95lp4x-15"
	echo "oei:  eg. ddr, tcm"
	echo "Optional: DEBUG=1"
	exit -1
}

if [ $# -ne 2 ]; then
    usage
fi

_som=$1
_oei=$2
_debug=1

#cd `dirname $0`
#cdir=`pwd`

make board=${_som} oei=${_oei} DEBUG=${_debug} 2>&1 all
