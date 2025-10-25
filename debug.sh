#! /usr/bin/sh

PROGRAM_NAME="project_initializer"


run_gdbgui() {
  gdbgui -g "gdb --q" --args ./$PROGRAM_NAME test
}


cd build

if [ -e $PROGRAM_NAME ]; then
  run_gdbgui
else
  echo "$PROGRAM_NAME not found. please run configure.sh then build.sh"
fi
