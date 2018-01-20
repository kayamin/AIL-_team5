#!/bin/sh

#HOME="/home/omron/deep-learning-lecture/team5/openpose-work/"
HOME="/home/team05/Downloads/openpose/"

DIR_HOME="${HOME}/movie_sit-up/"

DIR_IN_PICT="${DIR_HOME}/2-2.COCO-pict/"
DIR_OUT_PICT="${DIR_HOME}/2-3.COCO-pict-mini/"

make_directory(){
    if [ ! -d $1 ]; then mkdir -p $1; fi
}

make_directory $DIR_OUT_PICT

# OpenPose 実行
for d in `ls -d $DIR_IN_PICT/*`
do
    echo "-----------"
    echo $d

    DIR_OUT_NOW=$DIR_OUT_PICT/`basename $d`
    make_directory $DIR_OUT_NOW
    for f in $d/*.*
    do
	echo $f
	g=${DIR_OUT_NOW}/`basename $f`
	convert $f -resize 10% $g
    done
done 
