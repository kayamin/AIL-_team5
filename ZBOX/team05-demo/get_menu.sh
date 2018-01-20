#!/bin/sh

#### Set your openpose directory
if [ `hostname` = "MLRA0860" ]
then
    HOME=`dirname $0`
else
    HOME="/home/team05/Downloads/openpose/"
fi

BIN_OPENPOSE="${HOME}/build/examples/user_code/1_extract_from_image_for-team5-demo.bin"
BIN_PYTHON="`dirname $0`/`basename $0 .sh`.py"
POSE_CSV="${HOME}/pose.csv"

#### main
cd $HOME
# OpenPose 実行
$BIN_OPENPOSE > $POSE_CSV
cd -
python $BIN_PYTHON $POSE_CSV
