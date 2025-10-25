#include <stdlib.h>
#include <stdio.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genCMakeListsFile(arena * program_arena)
{
  char * filename = "CMakeLists.txt";
  //  Check to see if the file already exists, and whether the user wants to overwrite it
  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * fp = fopen(filename, "r");
  fp = fopen(filename, "w");
  if (!fp)
  {
    printf("[%-20s] ERROR: failed to open file. Exiting", __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "cmake_minimum_required(VERSION 3.22.1)\n\n");
  fprintf(fp, "project(%s \nVERSION 0.0.0 \nLANGUAGES C\n)\n\n", program_arena->project_name);
  fprintf(fp, "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n");
  fprintf(fp, "set(CMAKE_BUILD_TYPE Debug)\n");
  fprintf(fp, "add_executable(${PROJECT_NAME} main.c)\n");
  fprintf(fp, "configure_file(${PROJECT_NAME}Config.h.in ${PROJECT_NAME}Config.h)\n\n");
  fprintf(fp, "list(APPEND MY_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR})\n");
  fprintf(fp, "list(APPEND MY_INCLUDE_DIRECTORIES ${PROJECT_BUILD_DIR})\n\n");
  fprintf(fp, "target_compile_options(${PROJECT_NAME} PRIVATE -Werror)\n");
  fprintf(fp, "\
if (CMAKE_BUILD_TYPE STREQUAL Debug)\n\
  target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)\n\
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)\n\
  target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)\n\
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)\n\
endif()\
\n\n");


  fprintf(fp, "\
target_include_directories(${PROJECT_NAME}\n\
        PRIVATE ${MY_INCLUDE_DIRECTORIES}\n\
)");

  fclose(fp);
}

