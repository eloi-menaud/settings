#!/bin/bash

for f in $(find . -maxdepth 1 -type l)
do
    cp --remove-destination $(readlink -e $f) $f
done