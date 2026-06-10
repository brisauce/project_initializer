#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>

#include "program_arena.h"
#include "check_overwrite.h"
#include "build/project_initializerConfig.h"
#include "file_to_buf.h"
#define CONFIGURE_SCRIPT_SOURCE ASSET_DIR "/configure.sh.txt"
#define FILENAME "configure.sh" 
#define PREFIXED_FILENAME DEBUG_PREFIX FILENAME
void genConfigScript(arena * program_arena)
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
    printf("[%-20s] ERROR: failed to open file %s. Exiting", filename, __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  char * source_filename = CONFIGURE_SCRIPT_SOURCE; 
  FILE * source_fp = fopen(source_filename, "r");
  assert(source_fp);

  buffer temp = {
    .buf_size = BUF_SIZE,
    .buf = calloc(1, temp.buf_size)
  };
  assert(temp.buf);

  copyFileToBuf(&temp, source_fp);

  fprintf(dest_fp, temp.buf, NULL);

  chmod(filename, S_IRWXU);
  free(temp.buf); 
  fclose(source_fp);
  fclose(dest_fp);
}
