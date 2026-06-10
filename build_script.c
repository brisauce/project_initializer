#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "program_arena.h"
#include "check_overwrite.h"
#include "file_to_buf.h"
#include "build/project_initializerConfig.h"

#define BUILD_SCRIPT_SOURCE ASSET_DIR "/build.sh.txt"
#define FILENAME "build.sh" 
#define PREFIXED_FILENAME DEBUG_PREFIX FILENAME
void genBuildScript(arena * program_arena)
{
  char * filename;

  if (program_arena->debug)
  {
    filename = PREFIXED_FILENAME;
  }
  else
  {
    filename = FILENAME;
  }
  

  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * dest_fp = fopen(filename, "w");

  if (!dest_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  char * source_filename = BUILD_SCRIPT_SOURCE;
  FILE * source_fp = fopen(source_filename, "r");

  if (!source_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, source_filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  buffer temp;
  temp.buf_size = 1024;
  temp.buf = calloc(1, temp.buf_size);
  copyFileToBuf(&temp, source_fp);

  fprintf(dest_fp, temp.buf, NULL /*This is just so the compiler will shut up about this being insecure*/);
  chmod(filename, S_IRWXU);

  free(temp.buf);
  fclose(dest_fp);
  fclose(source_fp);
}
