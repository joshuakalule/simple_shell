#!/usr/bin/sh

betty ../main.h
# Compile and run all main-*.c files in the current directory
for file in ../*.c; do
	if [ -f "$file" ]; then
		betty "$file"	
	fi
done
