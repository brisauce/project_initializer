#include <stdio.h>
#include <assert.h>

#include "copyfile.h"
#include "program_arena.h"
#include "build/project_initializerConfig.h"
#include "check_overwrite.h"
#define FILENAME ".gitignore" 
#define SOURCE_FILE ASSET_DIR "/gitignore_template.txt"
void genGitignore(arena * a)
{
  char * filename;
  if (a->debug)
  {
    filename = DEBUG_PREFIX FILENAME;
  }
  else
  {
    filename = FILENAME;
  }

  if (!canOverwrite(filename))
  {
    return;
  }
  FILE * source_fp = fopen(SOURCE_FILE, "r");
  assert(source_fp);
  FILE * dest_fp = fopen(filename, "w");
  assert(dest_fp);
  //  "0" for the start of the file, copying the whole file into the 
  //  destination file location
  copyFile(source_fp, 0, dest_fp, 0);
  fclose(source_fp);
  fclose(dest_fp);
}
