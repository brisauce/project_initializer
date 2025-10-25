#! /usr/bin/sh

PROGRAM_NAME="project_initializer"


run_program () {
  ./$PROGRAM_NAME test.
}

if [ ! -d build ]; then
  echo "Build directory not found. Please run configure.sh to generate build files."
  # general error code when exiting shell script, according to stack overflow
  exit 1
fi

cd build

if [ -e $PROGRAM_NAME ]; then
  run_program
else
  echo "$PROGRAM_NAME not found. Please run build.sh."
fi

