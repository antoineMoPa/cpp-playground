#!/bin/bash

SOME_FONTS=$(convert -list font | grep Font: | tr -s " " | grep -v jsMath | sed "s/ Font: //")

mkdir fonts
cd fonts

root_folder=$PWD

counter=0

for font in $SOME_FONTS; do
    mkdir $font
    cd $font
    if [[ $counter > 20 ]];
    then
	# enough fonts already
	exit;
    fi
       
    for i in {a..z} {A..Z};
    do
	convert -font $font label:$i $i.png;
    done
    cd $root_folder;
    counter=$(($counter+1))
done
