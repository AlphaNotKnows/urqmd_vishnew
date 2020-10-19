#! /usr/bin/env bash

# check argument and get directories
if [ $# -le 2 ]
then
  echo "Usage: hydroWithInitialCondition.sh source_folder destination_folder hydro_executable and parameters"
  exit
else
  sourceDir=$1
  targetDir=$2
fi

current_dir=`pwd`

# get hydro_executable and parameters
executable=""
while [ $# -gt 2 ]
do
  arg=`echo "$3" | sed 's/ /\?/g'`
  executable="$executable $arg"
  shift
done

# copy initial conditions
for file1 in `ls $sourceDir`
do
  rm ./Initial/*
  echo
  echo =================================================================
  echo
  echo Using $sourceDir/"$file1"...
  cp $sourceDir/"$file1" ./Initial
  cp ./Initial/"$file1" ./Initial/InitialSd.dat
  ./record-hydro.py $targetDir $executable
  echo
done
