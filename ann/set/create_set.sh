#!/bin/bash

for i in {a..z} {A..Z};
do
    convert label:$i $i.png;
done
