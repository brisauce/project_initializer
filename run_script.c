#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

#include "program_arena.h"
#include "check_overwrite.h"
#include "build/project_initializerConfig.h"
#include "file_to_buf.h"

#define RUN_SCRIPT_FILE ASSET_DIR "/run.sh.txt" 
#define FILENAME "run.sh" 
#define PREFIXED_FILENAME DEBUG_PREFIX FILENAME

void genRunScript(arena * program_arena)
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

  FILE * source_fp = fopen(RUN_SCRIPT_FILE, "r");

  if (!dest_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, filename);
  }

  buffer buff = {
    .buf_size = 1024,
  };
  buff.buf = calloc(1, buff.buf_size);
  assert(buff.buf);
  copyFileToBuf(&buff, source_fp);
  
  fprintf(dest_fp, buff.buf, program_arena->project_name); 
  
  chmod(filename, S_IRWXU);

  free(buff.buf);
  fclose(dest_fp);
  fclose(source_fp);
}
