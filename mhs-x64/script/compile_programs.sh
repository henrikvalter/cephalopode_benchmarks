#!/bin/sh

MHS=mhs

for x in src_arb/*.hs src_fixed/*.hs; do
    fname=`basename "$x"`
    echo "Compiling $fname"
    name="${fname%%.hs}"
    MHSDIR="mhs-callgrind" ${MHS} -isrc_arb -isrc_fixed -i../input/mhs -obin/"$name" "$name"
done
