#!/bin/bash

for exe in bin/*; do
	name=`basename "$exe"`
    echo "Gathering data for $name"
	valgrind --quiet --tool=callgrind --instr-atstart=no --callgrind-out-file=callgrind/"$name".txt "$exe"
done
grep total callgrind/*
