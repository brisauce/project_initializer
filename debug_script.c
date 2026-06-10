#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "program_arena.h"
#include "check_overwrite.h"
#include "build/project_initializerConfig.h"
#include "file_to_buf.h" 
#define DEBUG_SCRIPT_SOURCE_FILE ASSET_DIR "/debug.sh.txt" 
#define FILENAME "debug.sh" 
#define PREFIXED_FILENAME DEBUG_PREFIX FILENAME
void genDebugScript(arena * program_arena) 
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

  char * source_filename = DEBUG_SCRIPT_SOURCE_FILE;
  FILE * source_fp = fopen(source_filename, "r");

  if (!source_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, source_filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  buffer temp = {.buf_size = BUF_SIZE};
  temp.buf = calloc(1, temp.buf_size);

  copyFileToBuf(&temp, source_fp); 
  fprintf(dest_fp, temp.buf, program_arena->project_name);

  chmod(filename, S_IRWXU);
  free(temp.buf);
  fclose(source_fp);
  fclose(dest_fp);
}

