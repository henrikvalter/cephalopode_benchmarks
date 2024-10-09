#!/bin/bash

cp -t src_fixed src_arb/Arb*.hs
rename Arb Fixed src_fixed/*

for x in src_fixed/*.hs; do
    sed -i 's/Integer/Int/g' "$x"
    sed -i 's/Arb/Fixed/g' "$x"
done
