#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genConfigHeader(arena * program_arena)
{
  char * suffix = "Config.h.in";
  if (strlen(suffix) + strlen(program_arena->project_name) > 100)
  {
    printf("ERROR: The project name %s is too long. Please choose a name containing up to %d characters",
           program_arena->project_name,
           (int) (100 - strlen(suffix)) );
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }
  
  char filename[100] = {0};

  strcpy(filename, program_arena->project_name);

  strcat(filename, suffix); 

  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * fp = fopen(filename, "w");

  if(!fp)
  {
    printf("[%-20s] ERROR: failed to open file. Exiting", __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "#define %s_VERSION_MAJOR ${%s_VERSION_MAJOR}\n",
          program_arena->project_name,
          program_arena->project_name);
  fprintf(fp, "#define %s_VERSION_MINOR ${%s_VERSION_MINOR}\n",
          program_arena->project_name,
          program_arena->project_name);
  fprintf(fp, "#define %s_VERSION_PATCH ${%s_VERSION_PATCH}\n\n\n",
          program_arena->project_name,
          program_arena->project_name);
  fprintf(fp, "#define PROJECT_NAME ${PROJECT_NAME}\n");

  fclose(fp);
}

void genMainDotC(arena * program_arena)
{
  char * filename = "main.c";

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
#include <stdio.h>\n\n\
#include \"%sConfig.h\"\n\
\n\
int main (int argc, char ** argv)\n\
{\n\
  printf(\"Wazzup\");\n\
}\n", program_arena->project_name);

  fclose(fp);
}

void genSourceFiles(arena * program_arena)
{
  genMainDotC(program_arena);
  genConfigHeader(program_arena);
}
