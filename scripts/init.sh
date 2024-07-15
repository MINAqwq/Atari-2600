#!/bin/sh

if [ -z "$1" ] || [ -z "$2" ]; then
	echo "$0 [COMPILER] [BUILD_TYPE]";
	echo "> BUILD_TYPE can be either Debug or Release";
	exit 1;
fi

cmake -S . -B ./build \
	-DCMAKE_C_COMPILER="$1" \
	-DCMAKE_BUILD_TYPE="$2" \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

