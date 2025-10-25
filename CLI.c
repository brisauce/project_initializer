#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program_arena.h"


arena * parseCLI (int argc, char ** argv)
{

  if (argc != 2)
  {
    puts("This program takes one argument, that being the name of the project being generated. Try again.");
    exit(EXIT_FAILURE);
  }

  arena * program_arena = calloc(1, sizeof(arena));

  strcpy(program_arena->project_name, argv[1]);

  return program_arena;
}
