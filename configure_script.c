#include <stdio.h>
#include <stdlib.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genConfigScript(arena * program_arena)
{
  char * filename = "configure.sh";

  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * fp = fopen(filename, "w");

  if (!fp)
  {
    printf("[%-20s] ERROR: failed to open file. Exiting", __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "\
#! /usr/bin/sh\n\
\n\
if [ -d build ]\n\
then\n\
  rm -rf ./build/\n\
fi\n\
\n\
cmake -S . -B ./build\n\
\n\
cd build/\n\
\n\
if [ -e compile_commands.json ]\n\
then\n\
  mv compile_commands.json ..\n\
else\n\
  echo \"ERROR: compile_commands.json not found in directory:\"\n\
  pwd\n\
fi\n");

  fclose(fp);
}
