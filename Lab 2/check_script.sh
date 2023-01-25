#!/bin/bash

FILE=lab2.c
BIN=lab2.bin.tmp
OUT=output.txt.tmp

if [ ! -f "$FILE" ]; then
    echo "ERROR: no file"
    exit
fi

gcc "$FILE" -o "$BIN"

if [ ! -f "$BIN" ]; then
    echo "ERROR: compile error"
    exit
fi    

# this is a sample command line
./"$BIN" input.txt.tmp 90 &> "$OUT"

RES=$(diff ans.txt.tmp output.txt.tmp | wc -l | tr -dc '0-9')

echo "Make sure to remove tmp files after"

if [ "$RES" -eq "0" ]; then
   echo "Compile/Run works";
   exit;
fi

echo "Compile/Run does NOT work";
