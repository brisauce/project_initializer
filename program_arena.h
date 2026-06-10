#ifndef PROGRAM_ARENA_H
#define PROGRAM_ARENA_H
#include <stdbool.h>

typedef struct {
  char project_name[100];
  bool debug;
}arena;

void freeArena (arena * program_arena);

#endif // !PROGRAM_ARENA_H
