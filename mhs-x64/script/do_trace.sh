#!/bin/bash

for exe in bin/*; do
	name=`basename "$exe"`
	trace --int3 trace/"$name".trace "$exe"
done
