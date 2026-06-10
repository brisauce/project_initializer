#include <stdlib.h>
#include <stdio.h>

#include "program_arena.h"
#include "check_overwrite.h"
#include "build/project_initializerConfig.h" 
#include "file_to_buf.h"

#define CMAKE_SOURCE_FILE ASSET_DIR "/CMakeLists.txt.txt"
void genCMakeListsFile(arena * program_arena)
{
  #define FILENAME "CMakeLists.txt" 
  char * filename;

  if (program_arena->debug)
  {
    filename = DEBUG_PREFIX FILENAME;
  }
  else 
  {
    filename = FILENAME;
  }

  //  Check to see if the file already exists, and whether the user wants to overwrite it
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

  char * source_filename = CMAKE_SOURCE_FILE;
  FILE * source_fp = fopen(source_filename, "r");
  if (!source_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, source_filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  buffer buff = {
    .buf_size = 1024,
  };
  buff.buf = calloc(1, buff.buf_size); 
  copyFileToBuf(&buff, source_fp);
  
  fprintf(dest_fp, buff.buf, program_arena->project_name);

  free(buff.buf);
  fclose(dest_fp);
  fclose(source_fp);
}

