#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "program_arena.h"
#include "build/project_initializerConfig.h"
#include "check_overwrite.h"
#include "file_to_buf.h"

#define MAINDOTC_ASSET_FILE ASSET_DIR "/main.c.txt" 
#define CONFIG_HEADER_FILE ASSET_DIR "/config_header.txt"

#define HDR_FILE_NAME_LEN 100 


void genConfigHeader(arena * program_arena)
{
  char * prefix = "";
  if (program_arena->debug)
  {
    prefix = DEBUG_PREFIX;
  }
  size_t prefix_len = strlen(prefix);
  char * suffix = "Config.h.in";
  size_t suffix_len = strlen(suffix);
  if (suffix_len + strlen(program_arena->project_name) + strlen(prefix) > HDR_FILE_NAME_LEN  )
  {
    printf("ERROR: The project name %s is too long. Please choose a name containing up to %d characters",
           program_arena->project_name,
           (int) (HDR_FILE_NAME_LEN - (suffix_len + prefix_len)) );
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }
  
  char filename[HDR_FILE_NAME_LEN] = {0};
  strcpy(filename, prefix);

  strcat(filename, program_arena->project_name);

  strcat(filename, suffix); 

  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * dest_fp = fopen(filename, "w");

  if(!dest_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", filename, __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }
  
  char * source_filename = CONFIG_HEADER_FILE;
  FILE * source_fp = fopen(source_filename, "r");

  if (!source_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", source_filename, __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  buffer temp = {
    .buf_size = 1024,
  };
  temp.buf = calloc(1, temp.buf_size);

  assert(temp.buf);
  copyFileToBuf(&temp, source_fp);

  fprintf(dest_fp, temp.buf, 
          program_arena->project_name,
          program_arena->project_name,
          program_arena->project_name,
          program_arena->project_name,
          program_arena->project_name,
          program_arena->project_name);

  free(temp.buf);
  fclose(source_fp);
  fclose(dest_fp);
}

void genMainDotC(arena * program_arena)
{
  #define MAIN_FILENAME "main.c" 
  char * main_filename;

  if (program_arena->debug)
  {
    main_filename = DEBUG_PREFIX MAIN_FILENAME;
  }
  else 
  {
    main_filename = MAIN_FILENAME;
  }

  if (!canOverwrite(main_filename))
  {
    return;
  }

  FILE * dest_fp = fopen(main_filename, "w");

  if (!dest_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, main_filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }
  
  char * source_filename = MAINDOTC_ASSET_FILE;
  FILE * source_fp = fopen(source_filename, "r");

  if (!source_fp)
  {
    printf("[%-20s] ERROR: failed to open file %s. Exiting", __func__, source_filename);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }
  buffer temp = {
    .buf_size = 1024,
  };
  temp.buf = calloc(1,temp.buf_size);

  assert(temp.buf);
  copyFileToBuf(&temp, source_fp); 

  //  The contents of the file copied into the destination file is already a format string with 
  //  all necessary specifiers included
  fprintf(dest_fp, temp.buf, program_arena->project_name);

  free(temp.buf);

  fclose(source_fp);
  fclose(dest_fp);
}

void genSourceFiles(arena * program_arena)
{
  genMainDotC(program_arena);
  genConfigHeader(program_arena);
}
