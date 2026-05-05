#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genRunScript(arena * program_arena)
{
  char * filename = "run.sh";

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
PROGRAM_NAME=\"%s\"\n\
\n\
\n\
run_program () {\n\
  ./$PROGRAM_NAME\n\
}\n\
\n\
if [ ! -d build ]; then\n\
  echo \"Build directory not found. Please run configure.sh to generate build files.\"\n\
  exit 1\n\
fi\n\
\n\
cd build\n\
\n\
if [ -e $PROGRAM_NAME ]; then\n\
  run_program\n\
else\n\
  echo \"$PROGRAM_NAME not found. Please run build.sh.\"\n\
fi\n", program_arena->project_name);
  chmod(filename, S_IRWXU);

  fclose(fp);
}
