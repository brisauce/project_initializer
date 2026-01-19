#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program_arena.h"
#include "build/project_initializerConfig.h"

void printHelp(void)
{
  printf("\
project_initializer version %d.%d.%d\n\
\n\
Example use:\n\
project_initializer (--help) \"project name\"\n\n\
This program generates project files for my (Brian) specific development setup.\n\
If a duplicate file to what this program would generate would be generated, the user will be prompted\n\
To tell the program whether or not to overwrite that file.\n",
         project_initializer_VERSION_MAJOR,
         project_initializer_VERSION_MINOR,
         project_initializer_VERSION_PATCH);
}

arena * parseCLI (int argc, char ** argv)
{

  if (argc != 2)
  {
    puts("This program takes one argument, that being the name of the project being generated. Try again.");
    exit(EXIT_FAILURE);
  }

  arena * program_arena = calloc(1, sizeof(arena));

  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-help") || !strcmp(argv[i], "help") || 
        !strcmp(argv[i], "--h"))
    {
      printHelp();
      free(program_arena);
      exit(EXIT_SUCCESS);
    }
    else
    {
      strcpy(program_arena->project_name, argv[1]);
    }
  }
  
  return program_arena;
}
