#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genBuildScript(arena * program_arena)
{
  char * filename = "build.sh";

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
if [ -d build ]\n\
then\n\
  cd build/\n\
  make\n\
else\n\
  echo \"Build folder not found. Please run configure.sh to generate build folder and necessary contents.\"\n\
fi\n\
");
  chmod(filename, S_IRWXU);

  fclose(fp);
}
