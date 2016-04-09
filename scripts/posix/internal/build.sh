#!/bin/sh

# first parameter is project directory
# second parameter is build directory
# other parameters are cmake arguments


start_dir="${PWD}"
echo start: $start_dir

# ensure project directory path is absolute 
cd $1
project_dir="${PWD}"
echo project: $project_dir


cd $start_dir


# remove build directory if it exists
if [ -d $2 ]
  then 
    echo deleting build folder...
    rm -r $2
fi


# create build directory and cd into it
mkdir $2
cd $2
echo build: "${PWD}"


# pop the first two arguments to this script
shift 2
echo $@

# run cmake, expanding the remaining arguments
echo cmake ${project_dir}  "$@" 
cmake ${project_dir}  "$@"



# build and run tests
make check

#return to start directory
cd $start_dir
